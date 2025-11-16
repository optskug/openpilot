from openpilot.system.ui.lib.application import gui_app
from tsk.c4.ui import ScalableBigButton, Layout, ScrollableBigDialog, ScrollableConfirmDialog
from tsk.common.key_file_manager import KeyFileManager


class Uninstaller(ScalableBigButton):
  def __init__(self):
    super().__init__(
      "TSK Uninstaller",
      click_callback=self.click,
      font_size=Layout.tools_row_button_font_size,
    )

  @staticmethod
  def click():
    key_manager = KeyFileManager()
    key = key_manager.installed_key

    if not key:
      message = "Key not installed.\n\n" \
                "Nothing to do."
      dialog = ScrollableBigDialog(description=message)
      gui_app.push_widget(dialog)
      return

    message = f"Key installed: {key}\n\n" \
              "Uninstall?"
    dialog = ScrollableConfirmDialog(
      description=message,
      confirm_callback=Uninstaller._do_reboot
    )
    gui_app.push_widget(dialog)

  @staticmethod
  def _do_reboot():
    key_manager = KeyFileManager()
    key_manager.uninstall_key()
