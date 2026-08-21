import os
import shutil

from tsk.lib.env import (
  ALTERNATE_OP_BRANCH,
  ALTERNATE_OP_DIR,
  ALTERNATE_OP_USER,
  CONTINUE_FILE,
  OPENPILOT_DIR,
  RECOMMENDED_OP_BRANCH,
  RECOMMENDED_OP_DIR,
  RECOMMENDED_OP_USER,
  is_agnos,
)
from tsk.lib.key_file_manager import KeyFileManager, format_key

REBOOT_ACTIONS = ("recommended", "alternate", "different", "retry")


class RebootManager:
  def __init__(self):
    self.is_agnos = is_agnos()

  @staticmethod
  def key_status_payload() -> dict:
    key = KeyFileManager().installed_key
    return {
      "installed": key is not None,
      "key": key,
    }

  def title(self, action: str) -> str:
    titles = {
      "recommended": f"Install {RECOMMENDED_OP_USER}/{RECOMMENDED_OP_BRANCH}",
      "alternate": f"Install {ALTERNATE_OP_USER}/{ALTERNATE_OP_BRANCH}",
      "different": "Install a different fork/branch",
      "retry": "Reboot to try again",
    }
    return titles[action]

  def prompt(self, action: str) -> str:
    key = KeyFileManager().installed_key
    if key:
      message = f"Key installed: {format_key(key)}\n\n"
    elif action == "retry":
      message = "!!!! Key not installed\n\n"
    else:
      message = "!!!! Key not installed\n!!!! Comma can't drive your car.\n\n"

    if action == "recommended":
      return message + f"Reboot and install {RECOMMENDED_OP_USER}/{RECOMMENDED_OP_BRANCH}?"
    if action == "alternate":
      return message + f"Reboot and install {ALTERNATE_OP_USER}/{ALTERNATE_OP_BRANCH}?"
    if action == "different":
      return message + "Reboot and install a different fork/branch?"
    if action == "retry":
      return message + "Reboot without changing anything?"
    raise ValueError(f"Unknown reboot action: {action}")

  def actions_payload(self) -> dict:
    return {
      action: {
        "label": self.title(action),
        "prompt": self.prompt(action),
      }
      for action in REBOOT_ACTIONS
    }

  def operations(self, action: str) -> list[str]:
    operations = {
      "recommended": [
        f"remove {OPENPILOT_DIR}",
        f"remove {ALTERNATE_OP_DIR}",
        f"move {RECOMMENDED_OP_DIR} to {OPENPILOT_DIR}",
        "reboot",
      ],
      "alternate": [
        f"remove {OPENPILOT_DIR}",
        f"remove {RECOMMENDED_OP_DIR}",
        f"move {ALTERNATE_OP_DIR} to {OPENPILOT_DIR}",
        "reboot",
      ],
      "different": [
        f"remove {RECOMMENDED_OP_DIR}",
        f"remove {ALTERNATE_OP_DIR}",
        f"remove {CONTINUE_FILE}",
        "reboot",
      ],
      "retry": [
        "reboot",
      ],
    }
    return operations[action]

  def execute(self, action: str) -> dict:
    if action not in REBOOT_ACTIONS:
      raise ValueError(f"Unknown reboot action: {action}")

    if not self.is_agnos:
      return {
        "ok": True,
        "dry_run": True,
        "title": self.title(action),
        "message": "Non-AGNOS safeguard active. No files changed.\n\nWould:\n" + "\n".join(f"- {op}" for op in self.operations(action)),
        **self.key_status_payload(),
      }

    # recommended/alternate rewrite /data/openpilot, the tree a live manager runs
    # from. Stop it first so the rmtree/move isn't pulled out from under it — the
    # matcher path can reach here with manager still alive (it doesn't kill it).
    if action in ("recommended", "alternate"):
      self._stop_manager()

    if action == "recommended":
      shutil.rmtree(OPENPILOT_DIR, ignore_errors=True)
      print(f"Removed {OPENPILOT_DIR}", flush=True)
      shutil.rmtree(ALTERNATE_OP_DIR, ignore_errors=True)
      print(f"Removed {ALTERNATE_OP_DIR}", flush=True)
      shutil.move(RECOMMENDED_OP_DIR, OPENPILOT_DIR)
      print(f"Moved {RECOMMENDED_OP_DIR} to {OPENPILOT_DIR}", flush=True)

    elif action == "alternate":
      shutil.rmtree(OPENPILOT_DIR, ignore_errors=True)
      print(f"Removed {OPENPILOT_DIR}", flush=True)
      shutil.rmtree(RECOMMENDED_OP_DIR, ignore_errors=True)
      print(f"Removed {RECOMMENDED_OP_DIR}", flush=True)
      shutil.move(ALTERNATE_OP_DIR, OPENPILOT_DIR)
      print(f"Moved {ALTERNATE_OP_DIR} to {OPENPILOT_DIR}", flush=True)

    elif action == "different":
      shutil.rmtree(RECOMMENDED_OP_DIR, ignore_errors=True)
      print(f"Removed {RECOMMENDED_OP_DIR}", flush=True)
      shutil.rmtree(ALTERNATE_OP_DIR, ignore_errors=True)
      print(f"Removed {ALTERNATE_OP_DIR}", flush=True)
      if os.path.exists(CONTINUE_FILE):
        os.remove(CONTINUE_FILE)
      print(f"Removed {CONTINUE_FILE}", flush=True)

    self.request_reboot()
    return {
      "ok": True,
      "dry_run": False,
      "title": self.title(action),
      "message": "Action confirmed. Reboot requested.",
      **self.key_status_payload(),
    }

  @staticmethod
  def _stop_manager() -> None:
    # Kill the manager (and pandad) before rewriting /data/openpilot so a live
    # manager isn't running from the tree we delete/move. tskweb is independent
    # and survives; SIGKILL skips manager_cleanup, and the reboot below recovers.
    import subprocess
    import time
    subprocess.run(["pkill", "-9", "-f", "manager.py"], check=False)
    subprocess.run(["pkill", "-9", "-f", "pandad"], check=False)
    time.sleep(2)

  @staticmethod
  def request_reboot() -> None:
    import subprocess
    subprocess.run(["sudo", "reboot"], check=False)
