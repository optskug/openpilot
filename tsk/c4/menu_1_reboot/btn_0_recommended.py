import shutil
import sys

from openpilot.system.ui.lib.application import gui_app
from tsk.c4.ui import ScalableBigButton, Layout, ScrollableConfirmDialog
from tsk.common.env import OPENPILOT_DIR, RECOMMENDED_OP_DIR, ALTERNATE_OP_DIR, RECOMMENDED_OP_USER, \
  RECOMMENDED_OP_BRANCH
from tsk.common.key_file_manager import KeyFileManager


class Recommended(ScalableBigButton):
  def __init__(self):
    super().__init__(
      f"Install {RECOMMENDED_OP_USER}/ {RECOMMENDED_OP_BRANCH}",
      click_callback=self.click,
      font_size=Layout.reboot_row_button_font_size,
    )

  @staticmethod
  def click():
    # Build confirmation message
    key = KeyFileManager().installed_key
    if key:
      message = f"Key installed: {key}\n\n"
    else:
      message = "!!!! Key not installed.\n" \
                "!!!! Comma can't drive your car.\n\n"
    message += f"Reboot and install {RECOMMENDED_OP_USER}/{RECOMMENDED_OP_BRANCH}?"

    dialog = ScrollableConfirmDialog(
      description=message,
      confirm_callback=Recommended._do_reboot
    )
    gui_app.push_widget(dialog)

  @staticmethod
  def _do_reboot():
    # Remove /data/openpilot since it won't be used
    shutil.rmtree(OPENPILOT_DIR, ignore_errors=True)
    print(f"Removed {OPENPILOT_DIR}")

    # Remove /data/tsk-alternate since it won't be used
    shutil.rmtree(ALTERNATE_OP_DIR, ignore_errors=True)
    print(f"Removed {ALTERNATE_OP_DIR}")

    # Move /data/tsk-alternate to /data/openpilot
    shutil.move(RECOMMENDED_OP_DIR, OPENPILOT_DIR)
    print(f"Moved {RECOMMENDED_OP_DIR} to {OPENPILOT_DIR}")

    sys.exit(0)
