import os
import shutil
import sys

from openpilot.system.ui.lib.application import gui_app
from tsk.c4.ui import ScalableBigButton, Layout, ScrollableConfirmDialog
from tsk.common.env import is_agnos, RECOMMENDED_OP_DIR, ALTERNATE_OP_DIR, CONTINUE_FILE
from tsk.common.key_file_manager import KeyFileManager


class SomethingElse(ScalableBigButton):
  def __init__(self):
    super().__init__(
      "Install a different fork/branch",
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
    message += "Reboot and install a different fork/branch?"

    dialog = ScrollableConfirmDialog(
      description=message,
      confirm_callback=SomethingElse._do_reboot
    )
    gui_app.push_widget(dialog)

  @staticmethod
  def _do_reboot():
    # Remove /data/tsk-recommended since it won't be used
    shutil.rmtree(RECOMMENDED_OP_DIR, ignore_errors=True)
    print(f"Removed {RECOMMENDED_OP_DIR}")

    # Remove /data/tsk-alternate since it won't be used
    shutil.rmtree(ALTERNATE_OP_DIR, ignore_errors=True)
    print(f"Removed {ALTERNATE_OP_DIR}")

    # /data/openpilot is deleted by the installer

    # Delete /data/continue.sh to trigger an installer without a reset
    if is_agnos():
      if os.path.exists(CONTINUE_FILE):
        os.remove(CONTINUE_FILE)
    print(f"Removed {CONTINUE_FILE}")

    sys.exit(0)
