# tsk/common/env.py
import os
import time


def is_agnos():
  return os.path.exists("/AGNOS")


COMMA_DATA_DIR = "/data" if is_agnos() else f"{os.path.expanduser('~')}/comma_data"

CONTINUE_FILE = f"{COMMA_DATA_DIR}/continue.sh"
OPENPILOT_DIR = f"{COMMA_DATA_DIR}/openpilot"
PAYLOAD_PATH = "/data/openpilot/tsk/common/payload.bin"

RECOMMENDED_OP_USER = "commaai"
RECOMMENDED_OP_BRANCH = "nightly-dev"
RECOMMENDED_OP_DIR = f"{COMMA_DATA_DIR}/tsk-recommended"
ALTERNATE_OP_USER = "sunnypilot"
ALTERNATE_OP_BRANCH = "staging"
ALTERNATE_OP_DIR = f"{COMMA_DATA_DIR}/tsk-alternate"


def is_calvins_comma() -> bool:
  try:
    with open("/persist/comma/dongle_id") as f:
      content = f.read()
      if "2decf199" in content or "d09634b" in content:
        return True

  except:
    pass

  return False


def is_cache_dir_new() -> bool:
  try:
    cache_dir = "/cache/params"
    mod_time = os.path.getmtime(cache_dir)
    age = time.time() - mod_time
    day = 60 * 60 * 24

    return age < day

  except:
    pass

  return False


def is_in_car() -> bool:
  return False
