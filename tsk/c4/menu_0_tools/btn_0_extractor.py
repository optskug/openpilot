import traceback

from openpilot.system.ui.lib.application import gui_app
from tsk.common.extractor import TSKExtractor, NotAGNOSError, BoarddNotRunningError, RetryError
from tsk.c4.ui import ScalableBigButton, Layout, ScrollableBigDialog
from tsk.common.key_file_manager import KeyFileManager


class Extractor(ScalableBigButton):
  def __init__(self):
    super().__init__(
      "TSK Extractor",
      click_callback=self.click,
      font_size=Layout.tools_row_button_font_size,
    )

  @staticmethod
  def click():
    try:
      secoc_key = TSKExtractor.hack()
      key_manager = KeyFileManager()
      key_manager.install_key(secoc_key)
      message = "Success!\n\n"
      message += "This is your key:\n"
      message += secoc_key + "\n\n"
      message += "Take a photo of your key."
      dialog = ScrollableBigDialog(description=message)
      gui_app.push_widget(dialog)
    except NotAGNOSError as e:
      message = str(e)
      dialog = ScrollableBigDialog(description=message)
      gui_app.push_widget(dialog)
    except (BoarddNotRunningError, RetryError) as e:
      message = f"Can't talk to the car: {e}"
      dialog = ScrollableBigDialog(description=message)
      gui_app.push_widget(dialog)
    except Exception as e:
      e.add_note("\n!!!! Unexpected error. Please take a photo, post it on #toyota-security, and ping @calvinspark\n")
      message = traceback.format_exc()
      dialog = ScrollableBigDialog(
        description=message,
        desc_font_size=15,
        scroll_to_bottom=True,
      )
      gui_app.push_widget(dialog)
