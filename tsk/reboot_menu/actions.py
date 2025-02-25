# tsk/reboot_menu/actions.py
import os
import shutil
import sys  # Import the sys module

from tsk.common.env import is_agnos, RELEASE_OP_BRANCH, RELEASES_OP_USER, NIGHTLY_OP_BRANCH, NIGHTLY_OP_USER
from tsk.common.key_file_manager import KeyFileManager
from tsk.ui.dialog import YesNoDialog


class Rebooter:
  # Actions based on launch_chffrplus.sh
  # Reboot is handled in that sh

  CONTINUE_FILE = "/data/continue.sh"
  OPENPILOT_DIR = "/data/openpilot"
  TSK_RELEASE_DIR = "/data/tsk-release"  # Must match installer.cc
  TSK_NIGHTLY_DIR = "/data/tsk-nightly"  # Must match installer.cc

  def __init__(self):
    self.is_agnos: bool = is_agnos()

  def release_action(self):
    print("Release button pressed")
    key = KeyFileManager().installed_key
    if key:
      question = f"Key installed: {key}\n\n"
    else:
      question = "!!!! Key not installed.\n" \
                 "!!!! Comma can't drive your car.\n\n"
    question += f"Reboot and install {RELEASES_OP_USER}/{RELEASE_OP_BRANCH}?"
    should_reboot = YesNoDialog.ask(question)
    if not should_reboot:
      print("Action cancelled")
      return
    print("Action confirmed")

    # Remove /data/openpilot
    if self.is_agnos:
      shutil.rmtree(self.OPENPILOT_DIR, ignore_errors=True)
    print(f"Removed {self.OPENPILOT_DIR}")

    # Remove /data/tsk-nightly
    if self.is_agnos:
      shutil.rmtree(self.TSK_NIGHTLY_DIR, ignore_errors=True)
    print(f"Removed {self.TSK_NIGHTLY_DIR}")

    # Move /data/tsk-release to /data/openpilot
    if self.is_agnos:
      shutil.move(self.TSK_RELEASE_DIR, self.OPENPILOT_DIR)
    print(f"Moved {self.TSK_RELEASE_DIR} to {self.OPENPILOT_DIR}")

    sys.exit(0)

  def nightly_action(self):
    print("Nightly button pressed")
    key = KeyFileManager().installed_key
    if key:
      question = f"Key installed: {key}\n\n"
    else:
      question = "!!!! Key not installed.\n" \
                 "!!!! Comma can't drive your car.\n\n"
    question += f"Reboot and install {NIGHTLY_OP_USER}/{NIGHTLY_OP_BRANCH}?"
    should_reboot = YesNoDialog.ask(question)
    if not should_reboot:
      print("Action cancelled")
      return
    print("Action confirmed")

    # Remove /data/openpilot
    if self.is_agnos:
      shutil.rmtree(self.OPENPILOT_DIR, ignore_errors=True)
    print(f"Removed {self.OPENPILOT_DIR}")

    # Remove /data/tsk-release
    if self.is_agnos:
      shutil.rmtree(self.TSK_RELEASE_DIR, ignore_errors=True)
    print(f"Removed {self.TSK_RELEASE_DIR}")

    # Move /data/tsk-nightly to /data/openpilot
    if self.is_agnos:
      shutil.move(self.TSK_NIGHTLY_DIR, self.OPENPILOT_DIR)
    print(f"Moved {self.TSK_NIGHTLY_DIR} to {self.OPENPILOT_DIR}")

    sys.exit(0)

  def bail_action(self):
    print("Bail button pressed")
    key = KeyFileManager().installed_key
    if key:
      question = f"Key installed: {key}\n\n"
    else:
      question = "!!!! Key not installed.\n" \
                 "!!!! Comma can't drive your car.\n\n"
    question += "Reboot and install a different fork/branch?"
    should_reboot = YesNoDialog.ask(question)
    if not should_reboot:
      print("Action cancelled")
      return
    print("Action confirmed")

    # Remove /data/tsk-release since it won't be used
    if self.is_agnos:
      shutil.rmtree(self.TSK_RELEASE_DIR, ignore_errors=True)
    print(f"Removed {self.TSK_RELEASE_DIR}")

    # Remove /data/tsk-nightly since it won't be used
    if self.is_agnos:
      shutil.rmtree(self.TSK_NIGHTLY_DIR, ignore_errors=True)
    print(f"Removed {self.TSK_NIGHTLY_DIR}")

    # /data/openpilot is deleted by the installer

    # Delete /data/continue.sh to trigger an installer without a reset
    if self.is_agnos:
      if os.path.exists(self.CONTINUE_FILE):
        os.remove(self.CONTINUE_FILE)
    print(f"Removed {self.CONTINUE_FILE}")

    sys.exit(0)

  def retry_action(self):
    print("Retry button pressed")
    key = KeyFileManager().installed_key
    if key:
      question = f"Key installed: {key}\n\n"
    else:
      question = "!!!! Key not installed.\n\n"
    question += "Reboot without changing anything?"
    should_reboot = YesNoDialog.ask(question)
    if not should_reboot:
      print("Action cancelled")
      return
    print("Action confirmed")

    # Do nothing
    sys.exit(0)
