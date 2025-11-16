from openpilot.system.ui.lib.application import gui_app
from tsk.c4.ui import ScalableBigButton, Layout, ScrollableBigDialog
from tsk.common.env import RECOMMENDED_OP_USER, RECOMMENDED_OP_BRANCH, is_in_car, is_cache_dir_new
from tsk.common.key_file_manager import KeyFileManager


class Guide(ScalableBigButton):
  def __init__(self):
    super().__init__(
      "Tell me what to do next",
      click_callback=self.click,
      font_size=Layout.tools_row_button_font_size,
    )

  @staticmethod
  def click():
    """Action to perform when the 'Tell me what to do next' button is pressed."""
    text = ""
    if KeyFileManager().installed_key:
      text += "Security key is installed.\n\n"
      text += "If you are selling your device, run TSK Uninstaller.\n\n"
      text += f"Otherwise, go to the Reboot Menu and install {RECOMMENDED_OP_USER}/{RECOMMENDED_OP_BRANCH}."

    else:
      if is_cache_dir_new():
        text += "Congratulations on your new comma!\n\n"
      else:
        text += "Security key is not installed.\n\n"

      text += "If you know your key, run TSK Keyboard to install it.\n\n"
      text += "Otherwise, "
      if not is_in_car():
        text += "go to your car and "
      text += "run TSK Extractor."

    dialog = ScrollableBigDialog(description=text)
    gui_app.push_widget(dialog)
