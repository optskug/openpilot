from tsk.c4.ui import ScalableBigButton, Layout


class Keyboard(ScalableBigButton):
  def __init__(self):
    super().__init__(
      "TSK Keyboard",
      click_callback=self.click,
      font_size=Layout.tools_row_button_font_size,
    )

  @staticmethod
  def click():
    print("TSK Keyboard clicked")
