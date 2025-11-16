import sys

from openpilot.system.ui.lib.application import gui_app
from tsk.c4.ui import ScalableBigButton, Layout, ScrollableConfirmDialog
from tsk.common.key_file_manager import KeyFileManager


class Reboot(ScalableBigButton):
  def __init__(self):
    super().__init__(
      "Reboot to try again",
      click_callback=self.click,
      font_size=Layout.reboot_row_button_font_size,
    )

  @staticmethod
  def click():
    """Action to perform when the 'Reboot to try again' button is pressed."""
    # Build confirmation message
    key = KeyFileManager().installed_key
    if key:
      message = f"Key installed: {key}\n\n"
    else:
      message = "!!!! Key not installed.\n\n"
    message += "Reboot without changing anything?"

    dialog = ScrollableConfirmDialog(
      description=message,
      confirm_callback=Reboot._do_reboot
    )
    gui_app.push_widget(dialog)

  @staticmethod
  def _do_reboot():
    """Actually perform the reboot."""
    print("Reboot confirmed - exiting to trigger reboot")
    # Do nothing - just exit, which triggers a reboot
    sys.exit(0)
