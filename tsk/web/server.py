#!/usr/bin/env python3
import json
import mimetypes
import os
from pathlib import Path
import socket
import subprocess
import threading
import time
import traceback
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import unquote, urlparse

from tsk.lib.collect_can import collect as collect_can, count_oracle_frames, oracle_path as can_oracle_path, PROTECTED_TARGET, SYNC_TARGET
from tsk.lib.dump_dataflash import DUMP_TOTAL, dump as dump_dataflash, dump_path
from tsk.lib.env import is_agnos, setup
from tsk.lib.extractor import NotAGNOSError, RetryError, TSKExtractor
from tsk.lib.key_file_manager import KeyFileManager, format_key
from tsk.lib.matcher import run as run_matcher
from tsk.lib.reboot_manager import REBOOT_ACTIONS, RebootManager


HOST = "0.0.0.0"
PORT = 11111
ASSET_DIR = Path(__file__).resolve().with_name("static")
OFFROAD_ALERT_PARAM = "Offroad_NoFirmware"
OFFROAD_ALERT_INTERVAL = 5.0

# Shared tail for the unexpected-error surfaces (extract + match). The leading
# "!!!!" makes index.html's modal render it red; the extractor terminal prints it
# verbatim. Kept in one place so the two paths can't drift.
PING_REPORT = ("!!!! Unexpected error. Please take a screenshot, post it on "
               "#toyota-security, and ping @calvinspark")

last_alert_url: str | None = None
# One physical panda: extract, dump, and collect must not run concurrently. Held
# for the whole operation (extract in the request thread; dump/collect in their
# job threads, released in the job's finally).
panda_lock = threading.Lock()
matcher_lock = threading.Lock()


def append_address(addresses: list[str], ip: str) -> None:
  if ip and not ip.startswith("127.") and ip not in addresses:
    addresses.append(ip)


def get_ipv4_addresses() -> list[str]:
  addresses: list[str] = []

  try:
    output = subprocess.check_output(
      ["ip", "-o", "-4", "route", "get", "1.1.1.1"],
      encoding="utf-8",
      stderr=subprocess.DEVNULL,
      timeout=1.0,
    )
    parts = output.split()
    if "src" in parts:
      append_address(addresses, parts[parts.index("src") + 1])
  except (OSError, subprocess.SubprocessError, TimeoutError):
    pass

  try:
    for info in socket.getaddrinfo(socket.gethostname(), None, socket.AF_INET):
      append_address(addresses, info[4][0])
  except OSError:
    pass

  # AGNOS devices have the `ip` utility, and it tends to be more accurate than
  # hostname lookups for hotspot and garage Wi-Fi testing.
  try:
    output = subprocess.check_output(
      ["ip", "-o", "-4", "addr", "show", "scope", "global"],
      encoding="utf-8",
      stderr=subprocess.DEVNULL,
      timeout=1.0,
    )
    for line in output.splitlines():
      parts = line.split()
      if "inet" not in parts:
        continue

      cidr = parts[parts.index("inet") + 1]
      append_address(addresses, cidr.split("/", 1)[0])
  except (OSError, subprocess.SubprocessError, TimeoutError):
    pass

  return addresses


def get_tsk_url() -> str | None:
  addresses = get_ipv4_addresses()
  return f"http://{addresses[0]}:{PORT}" if addresses else None


def get_params_dir() -> Path:
  params_root = Path(os.getenv("PARAMS_ROOT", "/data/params"))
  params_prefix = os.getenv("OPENPILOT_PREFIX", "d") or "d"
  return params_root / params_prefix


def get_reboot_actions_payload() -> dict:
  reboot_manager = RebootManager()
  payload = {
    "is_agnos": is_agnos(),
    "dry_run": not reboot_manager.is_agnos,
  }
  payload.update(reboot_manager.actions_payload())
  return payload


def run_reboot_action(action: str) -> tuple[HTTPStatus, dict]:
  if action not in REBOOT_ACTIONS:
    return HTTPStatus.BAD_REQUEST, {
      "ok": False,
      "error": "bad_action",
      "title": "Unknown action",
      "message": f"Unknown reboot action: {action}",
      **RebootManager.key_status_payload(),
    }

  try:
    return HTTPStatus.OK, RebootManager().execute(action)
  except Exception as e:
    return HTTPStatus.INTERNAL_SERVER_ERROR, {
      "ok": False,
      "error": "unexpected",
      "title": "Unexpected error",
      "message": str(e),
      "traceback": traceback.format_exc(),
      **RebootManager.key_status_payload(),
    }


def write_offroad_alert(url: str | None) -> bool:
  params_dir = get_params_dir()
  if not params_dir.exists():
    return False

  alert_path = params_dir / OFFROAD_ALERT_PARAM
  if url is None:
    try:
      alert_path.unlink()
    except FileNotFoundError:
      pass
    return True

  payload = json.dumps({"text": "%1", "severity": 0, "extra": url}, sort_keys=True)
  tmp_path = params_dir / f".tmp_{OFFROAD_ALERT_PARAM}_{os.getpid()}"

  with open(tmp_path, "w", encoding="utf-8") as f:
    f.write(payload)
    f.flush()
    os.fsync(f.fileno())

  os.replace(tmp_path, alert_path)

  try:
    dir_fd = os.open(params_dir, os.O_RDONLY)
    try:
      os.fsync(dir_fd)
    finally:
      os.close(dir_fd)
  except OSError:
    pass

  return True


def update_offroad_alert() -> None:
  global last_alert_url

  url = get_tsk_url()
  # The manager wipes Offroad_NoFirmware on start (CLEAR_ON_MANAGER_START) and on
  # the onroad transition, out from under us. Rewrite when the URL changed or the
  # file is gone — trusting last_alert_url alone masks the deletion and the alert
  # never returns.
  alert_path = get_params_dir() / OFFROAD_ALERT_PARAM
  if url == last_alert_url and (url is None or alert_path.exists()):
    return

  try:
    if write_offroad_alert(url):
      last_alert_url = url
  except OSError as e:
    print(f"TSK Manager Web could not update offroad alert: {e}", flush=True)


def offroad_alert_loop() -> None:
  while True:
    update_offroad_alert()
    time.sleep(OFFROAD_ALERT_INTERVAL)


def resolve_asset(path: str) -> Path | None:
  relative_path = "index.html" if path in ("", "/") else unquote(path).lstrip("/")
  if relative_path.endswith("/"):
    relative_path += "index.html"

  relative = Path(relative_path)
  if relative.is_absolute() or ".." in relative.parts:
    return None

  candidate = (ASSET_DIR / relative).resolve()
  try:
    candidate.relative_to(ASSET_DIR.resolve())
  except ValueError:
    return None

  if candidate.is_file():
    return candidate

  return None


def content_type_for(path: Path) -> str:
  content_type, _ = mimetypes.guess_type(path.name)
  content_type = content_type or "application/octet-stream"
  if content_type.startswith("text/") or content_type in ("application/javascript", "application/json"):
    content_type += "; charset=utf-8"
  return content_type


DRY_RUN_FAKE_KEY = "a1b2c3d4e5f6a7b8a1b2c3d4e5f6a7b8"
dry_run_counter = 0

# CAN collection runs as a background job, mirroring the DataFlash job below.
# can_state is the live progress the status endpoint reports; the collect thread
# owns writes under can_lock. ready == (status == "complete").
can_lock = threading.Lock()
can_state = {
  "ready": False,
  "status": "idle",   # idle | running | complete | insufficient | failed
  "sync_count": 0,
  "protected_count": 0,
  "seconds": 0.0,
  "message": "",
}

# DataFlash dump runs as a background job. df_state is the live progress the
# status endpoint reports; the dump thread owns writes to it under df_lock.
# ready == (status == "complete") so the UI's existing green-dot gating holds.
df_lock = threading.Lock()
df_state = {
  "ready": False,
  "status": "idle",   # idle | running | complete | partial | key_missed | failed
  "frames": 0,
  "bytes": 0,
  "total": DUMP_TOTAL,
  "message": "",
  "size": 0,
}


def _df_progress(status=None, frames=None, bytes_done=None, total=None, message=None) -> None:
  with df_lock:
    if status is not None:
      df_state["status"] = status
    if frames is not None:
      df_state["frames"] = frames
    if bytes_done is not None:
      df_state["bytes"] = bytes_done
    if total is not None:
      df_state["total"] = total
    if message is not None:
      df_state["message"] = message


def _run_dataflash_mock() -> None:
  # Laptop dry run: ramp progress over a couple of seconds so the collector page
  # shows movement, then land on complete. The partial/key_missed paths only happen
  # on a real device.
  for done in (4096, 8192, 16384, 24576, DUMP_TOTAL):
    time.sleep(0.4)
    _df_progress(status="running", frames=done // 4, bytes_done=done, total=DUMP_TOTAL)
  with df_lock:
    df_state.update(status="complete", frames=DUMP_TOTAL // 4, bytes=DUMP_TOTAL,
                    total=DUMP_TOTAL, size=DUMP_TOTAL, ready=True,
                    message=f"Dump complete: {DUMP_TOTAL} bytes (mock).")


def _run_dataflash_job() -> None:
  try:
    result = dump_dataflash(progress_cb=_df_progress)
    status = result.get("status", "failed")
    with df_lock:
      df_state.update(
        status=status,
        frames=result.get("frames", df_state["frames"]),
        bytes=result.get("bytes", df_state["bytes"]),
        total=result.get("total", DUMP_TOTAL),
        message=result.get("message", ""),
        ready=(status == "complete"),
        size=result.get("bytes", 0) if status == "complete" else 0,
      )
  except NotAGNOSError:
    _run_dataflash_mock()
  except Exception as e:
    with df_lock:
      df_state.update(status="failed", message=str(e), ready=False, size=0)
  finally:
    TSKExtractor._close_panda()
    panda_lock.release()


def start_dataflash_job() -> bool:
  # panda_lock is the gate: a running extract/dump/collect holds it, so a
  # concurrent dump is rejected here. The job thread releases it in its finally.
  if not panda_lock.acquire(blocking=False):
    return False
  with df_lock:
    df_state.update(status="running", frames=0, bytes=0, total=DUMP_TOTAL,
                    message="", ready=False, size=0)
  try:
    threading.Thread(target=_run_dataflash_job, name="tsk_dataflash_dump", daemon=True).start()
  except Exception:
    # The job thread never took ownership, so release the lock and clear the state
    # here — otherwise panda_lock would wedge every panda op until a restart.
    with df_lock:
      df_state.update(status="failed", message="Could not start the dump job.", ready=False)
    panda_lock.release()
    return False
  return True


def clear_dataflash() -> bool:
  # Refuse while a dump is in flight: a completing dump would otherwise re-set the
  # state and re-write the file this clear just removed. Returns False if running.
  with df_lock:
    if df_state["status"] == "running":
      return False
    df_state.update(ready=False, status="idle", frames=0, bytes=0,
                    total=DUMP_TOTAL, message="", size=0)
  for path in (dump_path(), Path(str(dump_path()) + ".partial")):
    try:
      path.unlink()
    except FileNotFoundError:
      pass
    except OSError:
      pass
  return True


def rehydrate_dataflash_state() -> None:
  # A completed dump persists on disk; reflect it after a restart so a finished
  # dump doesn't show as not-done and prompt a needless re-dump. A complete dump
  # is exactly DUMP_TOTAL bytes, so a truncated file can't masquerade as done.
  try:
    size = dump_path().stat().st_size
  except OSError:
    size = None
  if size == DUMP_TOTAL:
    with df_lock:
      df_state.update(ready=True, status="complete", frames=DUMP_TOTAL // 4,
                      bytes=DUMP_TOTAL, total=DUMP_TOTAL, size=DUMP_TOTAL,
                      message="Dump complete.")
    return
  # No complete dump, but a .partial sidecar means a near-complete run is on disk.
  # Reflect it as partial so Find stays enabled and the matcher falls back to it
  # after a restart (it finds the key in the captured range or asks for a re-dump).
  try:
    Path(str(dump_path()) + ".partial").stat()
  except OSError:
    return
  with df_lock:
    df_state.update(ready=False, status="partial", total=DUMP_TOTAL,
                    message="Partial dump on disk.\nTry the Find Toyota Security Key button.\n"
                            "If it doesn't work, restart the car into Not Ready To Drive mode and dump again.")


def _can_progress(seconds=None, sync=None, protected=None) -> None:
  with can_lock:
    if seconds is not None:
      can_state["seconds"] = seconds
    if sync is not None:
      can_state["sync_count"] = sync
    if protected is not None:
      can_state["protected_count"] = protected


def _run_can_mock() -> None:
  # Laptop dry run: ramp counts over a couple of seconds, then land on complete.
  for i in range(1, 7):
    time.sleep(0.4)
    _can_progress(seconds=i * 10.0, sync=i * 10, protected=i * 600)
  with can_lock:
    can_state.update(status="complete", ready=True, seconds=60.0,
                     sync_count=60, protected_count=3600,
                     message="Collected 60 sync and 3600 protected frames (mock).")


def _run_can_job() -> None:
  try:
    result = collect_can(progress_cb=_can_progress)
    status = result.get("status", "failed")
    with can_lock:
      can_state.update(
        status=status,
        sync_count=result.get("sync", can_state["sync_count"]),
        protected_count=result.get("protected", can_state["protected_count"]),
        message=result.get("message", ""),
        ready=(status == "complete"),
      )
  except NotAGNOSError:
    _run_can_mock()
  except Exception as e:
    with can_lock:
      can_state.update(status="failed", message=str(e), ready=False)
  finally:
    TSKExtractor._close_panda()
    panda_lock.release()


def start_can_job() -> bool:
  # panda_lock is the gate: a running extract/dump/collect holds it, so a
  # concurrent collect is rejected here. The job thread releases it in its finally.
  if not panda_lock.acquire(blocking=False):
    return False
  with can_lock:
    can_state.update(status="running", sync_count=0, protected_count=0,
                     seconds=0.0, message="", ready=False)
  try:
    threading.Thread(target=_run_can_job, name="tsk_can_collect", daemon=True).start()
  except Exception:
    # Same as the dump: release the lock and clear the state if the thread that
    # would release it never starts.
    with can_lock:
      can_state.update(status="failed", message="Could not start the collection job.", ready=False)
    panda_lock.release()
    return False
  return True


def clear_can() -> bool:
  # Refuse while a collection is in flight so a finishing job can't resurrect the
  # oracle this clear just removed. Returns False if running.
  with can_lock:
    if can_state["status"] == "running":
      return False
    can_state.update(ready=False, status="idle", sync_count=0,
                     protected_count=0, seconds=0.0, message="")
  try:
    can_oracle_path().unlink()
  except FileNotFoundError:
    pass
  except OSError:
    pass
  return True


def rehydrate_can_state() -> None:
  # Reflect a persisted oracle as ready after a restart, mirroring the dump.
  sync, protected = count_oracle_frames()
  if sync >= SYNC_TARGET and protected >= PROTECTED_TARGET:
    with can_lock:
      can_state.update(ready=True, status="complete", sync_count=sync,
                       protected_count=protected,
                       message=f"Collected {sync} sync and {protected} protected frames.")


class TSKWebHandler(BaseHTTPRequestHandler):
  server_version = "TSKWeb/0.1"

  def _send_extract_dry_run(self) -> None:
    global dry_run_counter
    scenario = dry_run_counter % 3
    dry_run_counter += 1

    if scenario == 0:
      KeyFileManager().install_key(DRY_RUN_FAKE_KEY)
      self._send_json({
        "ok": True,
        "key": DRY_RUN_FAKE_KEY,
        "message": f"Success!\n\nThis is your key:\n{format_key(DRY_RUN_FAKE_KEY)}\n\nTake a screenshot now.",
      })
    elif scenario == 1:
      self._send_json({
        "ok": False,
        "message": "pandad is not running.\n\nTry again. If the problem persists, turn off the car, "
                   "put it back into 'Not Ready to Drive' mode, and then try again."
                   f"\n\n{PING_REPORT}",
      }, status=HTTPStatus.CONFLICT)
    else:
      self._send_json({
        "ok": False,
        "message": (
          "UDS request timed out\n\n"
          "Traceback (most recent call last):\n"
          '  File "/data/openpilot/tsk/lib/extractor.py", line 384, in run\n'
          "    secoc_key = cls.hack()\n"
          '  File "/data/openpilot/tsk/lib/extractor.py", line 241, in hack\n'
          "    seed = cls._security_access(panda)\n"
          '  File "/data/openpilot/tsk/lib/extractor.py", line 152, in _security_access\n'
          "    resp = cls._uds_request(panda, service=0x27, subfunction=0x01)\n"
          '  File "/data/openpilot/tsk/lib/extractor.py", line 113, in _uds_request\n'
          "    raise RetryError(f\"UDS request timed out\")\n"
          "tsk.lib.extractor.RetryError: UDS request timed out\n\n"
          "!!!! Unexpected error. Please take a screenshot, post it on #toyota-security, and ping @calvinspark\n"
        ),
      }, status=HTTPStatus.INTERNAL_SERVER_ERROR)

  def do_GET(self) -> None:
    self._handle_request(send_body=True)

  def do_HEAD(self) -> None:
    self._handle_request(send_body=False)

  def do_POST(self) -> None:
    path = urlparse(self.path).path

    if path == "/api/extract":
      if not panda_lock.acquire(blocking=False):
        self._send_json({
          "ok": False,
          "message": "Another panda operation (dump or CAN collect) is in progress.",
        }, status=HTTPStatus.CONFLICT)
        return

      try:
        secoc_key = TSKExtractor.hack()
        KeyFileManager().install_key(secoc_key)
        self._send_json({
          "ok": True,
          "key": secoc_key,
          "message": f"Success!\n\nThis is your key:\n{format_key(secoc_key)}\n\nTake a screenshot now.",
        })
      except NotAGNOSError:
        self._send_extract_dry_run()
        return
      except Exception as e:
        tb = traceback.format_exc()
        self._send_json({
          "ok": False,
          "message": f"{e}\n\n{tb}\n\n{PING_REPORT}",
        }, status=HTTPStatus.INTERNAL_SERVER_ERROR)
      finally:
        TSKExtractor._close_panda()
        panda_lock.release()
      return

    if path == "/api/match":
      if not matcher_lock.acquire(blocking=False):
        self._send_json({
          "ok": False,
          "status": "running",
          "message": "Key finder is already running.",
        }, status=HTTPStatus.CONFLICT)
        return

      try:
        result = run_matcher()
        if result["status"] == "found":
          KeyFileManager().install_key(result["key"])
          # Same body for a complete or a partial recovery — the title carries
          # "Success!", so the body opens straight at the key.
          detail = (
            f"Found at {result['address']} — {result['matches']} matches "
            f"(sync {result['sync']}, protected {result['protected']})."
          )
          message = (
            f"This is your key:\n{format_key(result['key'])}\n\n"
            f"{detail}\n\n"
            "Take a screenshot now."
          )
          self._send_json({
            "ok": True,
            "status": "found",
            "key": result["key"],
            "message": message,
            **RebootManager.key_status_payload(),
          })
        else:
          # Forward the matcher's debug fields; index.html builds the not-found
          # debug block from these plus the dump/oracle counts it already polls.
          self._send_json({
            "ok": False,
            "status": result["status"],
            "message": result["message"],
            "matches": result["matches"],
            "sync": result["sync"],
            "protected": result["protected"],
            "address": result["address"],
            "offset": result["offset"],
            "windows_scanned": result["windows_scanned"],
            "survivors": result["survivors"],
            "malformed": result["malformed"],
            "dump_partial": result["dump_partial"],
          })
      except Exception as e:
        tb = traceback.format_exc()
        self._send_json({
          "ok": False,
          "status": "error",
          "message": f"{e}\n\n{tb}\n\n{PING_REPORT}",
          "traceback": tb,
        }, status=HTTPStatus.INTERNAL_SERVER_ERROR)
      finally:
        matcher_lock.release()
      return

    if path == "/api/uninstall":
      try:
        key_manager = KeyFileManager()
        key_was_installed = key_manager.installed_key is not None
        key_manager.uninstall_key()
        self._send_json({
          "ok": True,
          "title": "Key removed" if key_was_installed else "Key not installed",
          "message": "Installed key removed." if key_was_installed else "Nothing to remove.",
          **RebootManager.key_status_payload(),
        })
      except Exception as e:
        self._send_json({
          "ok": False,
          "error": "unexpected",
          "title": "Unexpected error",
          "message": str(e),
          "traceback": traceback.format_exc(),
          **RebootManager.key_status_payload(),
        }, status=HTTPStatus.INTERNAL_SERVER_ERROR)
      return

    if path == "/api/reboot":
      try:
        request = self._read_json_body()
        status, payload = run_reboot_action(str(request.get("action", "")))
        self._send_json(payload, status=status)
      except Exception as e:
        self._send_json({
          "ok": False,
          "error": "unexpected",
          "title": "Unexpected error",
          "message": str(e),
          "traceback": traceback.format_exc(),
          **RebootManager.key_status_payload(),
        }, status=HTTPStatus.INTERNAL_SERVER_ERROR)
      return

    if path == "/api/can-collect":
      if not start_can_job():
        self._send_json({
          "ok": False,
          "status": "running",
          "message": "A CAN collection or another panda operation is already in progress.",
        }, status=HTTPStatus.CONFLICT)
        return
      self._send_json({"ok": True, "status": "running"})
      return

    if path == "/api/dataflash-dump":
      if not start_dataflash_job():
        self._send_json({
          "ok": False,
          "status": "running",
          "message": "A DataFlash dump or another panda operation is already in progress.",
        }, status=HTTPStatus.CONFLICT)
        return
      self._send_json({"ok": True, "status": "running"})
      return

    if path == "/api/clear-cache":
      with can_lock:
        can_running = can_state["status"] == "running"
      with df_lock:
        df_running = df_state["status"] == "running"
      if can_running or df_running:
        self._send_json({
          "ok": False,
          "status": "running",
          "message": "A collection or dump is in progress. Wait for it to finish, then clear.",
        }, status=HTTPStatus.CONFLICT)
        return
      clear_can()
      clear_dataflash()
      self._send_json({"ok": True})
      return

    self._send_json({"error": "not found"}, status=HTTPStatus.NOT_FOUND)

  def _handle_request(self, send_body: bool) -> None:
    path = urlparse(self.path).path

    if path == "/api/health":
      self._send_json({
        "status": "ok",
        "service": "tsk_web",
        "host": HOST,
        "port": PORT,
        "url": get_tsk_url(),
        "addresses": get_ipv4_addresses(),
        "asset_dir": str(ASSET_DIR),
        "dry_run": not is_agnos(),
        "is_agnos": is_agnos(),
      }, send_body=send_body)
      return

    if path == "/api/status":
      self._send_json(RebootManager.key_status_payload(), send_body=send_body)
      return

    if path == "/api/can-status":
      with can_lock:
        payload = dict(can_state)
      self._send_json(payload, send_body=send_body)
      return

    if path == "/api/dataflash-status":
      with df_lock:
        payload = dict(df_state)
      self._send_json(payload, send_body=send_body)
      return

    if path == "/api/reboot":
      try:
        self._send_json(get_reboot_actions_payload(), send_body=send_body)
      except Exception as e:
        self._send_json({
          "ok": False,
          "error": "unexpected",
          "title": "Unexpected error",
          "message": str(e),
          "traceback": traceback.format_exc(),
        }, status=HTTPStatus.INTERNAL_SERVER_ERROR, send_body=send_body)
      return

    if path == "/favicon.ico":
      self.send_response(HTTPStatus.NO_CONTENT)
      self.end_headers()
      return

    asset = resolve_asset(path)
    if asset is not None:
      self._send_bytes(HTTPStatus.OK, content_type_for(asset), asset.read_bytes(), send_body=send_body)
      return

    self._send_json({"error": "not found"}, status=HTTPStatus.NOT_FOUND, send_body=send_body)

  def _send_json(self, payload: dict, status: HTTPStatus = HTTPStatus.OK, send_body: bool = True) -> None:
    body = json.dumps(payload, sort_keys=True).encode("utf-8")
    self._send_bytes(status, "application/json; charset=utf-8", body, send_body=send_body)

  def _read_json_body(self) -> dict:
    length = int(self.headers.get("Content-Length", "0") or "0")
    if length <= 0:
      return {}
    raw_body = self.rfile.read(length)
    if not raw_body:
      return {}
    return json.loads(raw_body.decode("utf-8"))

  def _send_bytes(self, status: HTTPStatus, content_type: str, body: bytes, send_body: bool = True) -> None:
    self.send_response(status)
    self.send_header("Content-Type", content_type)
    self.send_header("Content-Length", str(len(body)))
    self.send_header("Cache-Control", "no-store")
    self.end_headers()
    if send_body:
      self.wfile.write(body)

  def log_message(self, fmt: str, *args: object) -> None:
    return


class TSKWebServer(ThreadingHTTPServer):
  allow_reuse_address = True
  daemon_threads = True


def main() -> None:
  setup()
  rehydrate_dataflash_state()
  rehydrate_can_state()
  update_offroad_alert()
  threading.Thread(target=offroad_alert_loop, name="tsk_offroad_alert", daemon=True).start()

  server = TSKWebServer((HOST, PORT), TSKWebHandler)
  print(f"TSK Manager Web listening on http://{HOST}:{PORT}", flush=True)
  for ip in get_ipv4_addresses():
    print(f"TSK Manager Web detected address: http://{ip}:{PORT}", flush=True)

  try:
    server.serve_forever()
  except KeyboardInterrupt:
    pass
  finally:
    server.server_close()


if __name__ == "__main__":
  main()
