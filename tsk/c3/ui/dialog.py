# tsk/c3/ui/dialog.py
"""
TSK Dialog widgets for full-screen dialogs with scrollable text.

Pure Widget architecture - NO platform detection needed.
"""

from typing import Optional

import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.scroll_panel import GuiScrollPanel
from tsk.c3.ui.button import TSKButton
from tsk.c3.ui.measure_text import measure_text
from tsk.c3.ui.render_loop import render_loop
from tsk.common.widget import TSKWidget

# Default font size for dialog buttons
DEFAULT_BUTTON_FONT_SIZE = 50


class BaseDialog(TSKWidget):
  """
  Base class for full-screen dialogs with scrollable text area.

  Provides common functionality for all dialog types:
  - Scrollable text area
  - Text wrapping
  - Layout management

  NO platform detection - pure Widget architecture.
  """

  BORDER_SIZE = 20
  BUTTON_HEIGHT = 80
  BUTTON_WIDTH = 310
  BUTTON_SPACING = 20
  FONT_SIZE = 70
  LINE_HEIGHT = FONT_SIZE * 1.1
  TEXT_PADDING = 10

  def __init__(self, body_text: str, font_size: int = FONT_SIZE, scroll_to_bottom: bool = False):
    super().__init__()
    self.body_text = body_text
    self.font_size = font_size
    self.scroll_to_bottom = scroll_to_bottom
    self.LINE_HEIGHT = self.font_size * 1.1

    self.textarea_rect = rl.Rectangle(
      self.BORDER_SIZE,
      self.BORDER_SIZE,
      gui_app.width - 2 * self.BORDER_SIZE,
      gui_app.height - 3 * self.BORDER_SIZE - self.BUTTON_HEIGHT
    )
    self.wrapped_lines = self._wrap_text(self.body_text, self.font_size, self.textarea_rect.width - 2 * self.TEXT_PADDING)
    self.content_height = len(self.wrapped_lines) * self.LINE_HEIGHT
    self.content_rect = rl.Rectangle(0, 0, self.textarea_rect.width - 2 * self.TEXT_PADDING, self.content_height)
    self.scroll_panel = GuiScrollPanel()
    self.scroll_offset = rl.Vector2(0, 0)
    self.initial_scroll_applied = False

  def render_text_area(self):
    """Render the scrollable text area."""
    scroll_y = self.scroll_panel.update(self.textarea_rect, self.content_rect)
    scroll = rl.Vector2(0, scroll_y)
    self.scroll_offset = scroll

    # Apply initial scroll to bottom after the first render
    if self.scroll_to_bottom and not self.initial_scroll_applied:
      self.scroll_offset.y = min(0, self.textarea_rect.height - self.content_height - 2 * self.TEXT_PADDING)
      self.initial_scroll_applied = True

    rl.begin_scissor_mode(int(self.textarea_rect.x), int(self.textarea_rect.y), int(self.textarea_rect.width), int(self.textarea_rect.height))
    y_offset = 0
    for line in self.wrapped_lines:
      position = rl.Vector2(self.textarea_rect.x + self.TEXT_PADDING + self.scroll_offset.x, self.textarea_rect.y + self.TEXT_PADDING + self.scroll_offset.y + y_offset)
      if position.y + self.LINE_HEIGHT < self.textarea_rect.y + self.TEXT_PADDING or position.y > self.textarea_rect.y + self.textarea_rect.height - self.TEXT_PADDING:
        y_offset += self.LINE_HEIGHT
        continue
      rl.draw_text_ex(gui_app.font(), line.strip(), position, self.font_size, 0, rl.WHITE)
      y_offset += self.LINE_HEIGHT
    rl.end_scissor_mode()

  def _wrap_text(self, text, font_size, max_width):
    """Wrap text to fit within max_width."""
    lines = []
    font = gui_app.font()

    # Split the text by newline characters
    for block in text.splitlines():
      if not block:  # Handle empty lines (consecutive newlines)
        lines.append("")
        continue

      current_line = ""
      for word in block.split():
        test_line = current_line + word + " "
        if measure_text(test_line, font_size).x <= max_width:
          current_line = test_line
        else:
          lines.append(current_line)
          current_line = word + " "
      if current_line:
        lines.append(current_line)

    return lines

  def _render(self, rect: rl.Rectangle):
    """Base render - subclasses should override."""
    pass


class OkayDialog(BaseDialog):
  """
  Full-screen dialog with scrollable text and an Okay button.

  NO platform detection - pure Widget architecture.
  """

  def __init__(self, body_text: str, font_size: int = BaseDialog.FONT_SIZE, scroll_to_bottom: bool = False, okay_text: str = "Okay"):
    super().__init__(body_text, font_size, scroll_to_bottom)
    self.okay_text = okay_text
    self.okay_clicked = False

    # Create okay button with green background
    self._okay_button = TSKButton(
      labels=[{"text": okay_text, "x_offset": 90, "y_offset": 10}],
      click_callback=self._on_okay,
      font_size=DEFAULT_BUTTON_FONT_SIZE,
      width=self.BUTTON_WIDTH,
      height=self.BUTTON_HEIGHT,
      background_color=rl.Color(20, 100, 20, 255)  # Green background
    )

  def _on_okay(self):
    """Handle okay button click."""
    self.okay_clicked = True

  @staticmethod
  def ask(body_text: str, font_size: int = BaseDialog.FONT_SIZE, scroll_to_bottom: bool = False, okay_text: str = "Okay") -> None:
    """Display a full-screen Okay dialog."""
    dialog = OkayDialog(body_text, font_size, scroll_to_bottom, okay_text)

    for _ in render_loop():
      if dialog.okay_clicked or rl.window_should_close():
        break

      dialog.render_text_area()

      # Calculate button position
      button_area_height = gui_app.height - dialog.textarea_rect.height - dialog.textarea_rect.y
      button_x = (gui_app.width - BaseDialog.BUTTON_WIDTH) / 2
      button_y = dialog.textarea_rect.y + dialog.textarea_rect.height + (button_area_height - BaseDialog.BUTTON_HEIGHT) / 2
      button_rect = rl.Rectangle(button_x, button_y, BaseDialog.BUTTON_WIDTH, BaseDialog.BUTTON_HEIGHT)

      # Render button (background color is handled by TSKButton now)
      dialog._okay_button.render(button_rect)


class YesNoDialog(BaseDialog):
  """
  Full-screen dialog with scrollable text and Yes/No buttons.

  NO platform detection - pure Widget architecture.
  """

  def __init__(self, body_text: str, font_size: int = BaseDialog.FONT_SIZE, scroll_to_bottom: bool = False, yes_text: str = "Yes", no_text: str = "No"):
    super().__init__(body_text, font_size, scroll_to_bottom)
    self.yes_text = yes_text
    self.no_text = no_text
    self.result = None

    # Create yes/no buttons with colored backgrounds
    self._yes_button = TSKButton(
      labels=[{"text": yes_text, "x_offset": 110, "y_offset": 10}],
      click_callback=lambda: self._set_result(True),
      font_size=DEFAULT_BUTTON_FONT_SIZE,
      width=self.BUTTON_WIDTH,
      height=self.BUTTON_HEIGHT,
      background_color=rl.Color(20, 100, 20, 255)  # Green background
    )
    self._no_button = TSKButton(
      labels=[{"text": no_text, "x_offset": 120, "y_offset": 10}],
      click_callback=lambda: self._set_result(False),
      font_size=DEFAULT_BUTTON_FONT_SIZE,
      width=self.BUTTON_WIDTH,
      height=self.BUTTON_HEIGHT,
      background_color=rl.Color(100, 20, 20, 255)  # Red background
    )

  def _set_result(self, value: bool):
    """Handle button clicks."""
    self.result = value

  @staticmethod
  def ask(body_text: str, font_size: int = BaseDialog.FONT_SIZE, scroll_to_bottom: bool = False, yes_text: str = "Yes", no_text: str = "No") -> Optional[bool]:
    """Display a full-screen Yes/No dialog and return user's choice."""
    dialog = YesNoDialog(body_text, font_size, scroll_to_bottom, yes_text, no_text)

    for _ in render_loop():
      if dialog.result is not None or rl.window_should_close():
        break

      dialog.render_text_area()

      # Calculate button positions
      button_top = gui_app.height - BaseDialog.BORDER_SIZE - BaseDialog.BUTTON_HEIGHT
      no_button_rect = rl.Rectangle(BaseDialog.BORDER_SIZE, button_top, BaseDialog.BUTTON_WIDTH, BaseDialog.BUTTON_HEIGHT)
      yes_button_rect = rl.Rectangle(gui_app.width - BaseDialog.BORDER_SIZE - BaseDialog.BUTTON_WIDTH, button_top, BaseDialog.BUTTON_WIDTH, BaseDialog.BUTTON_HEIGHT)

      # Render buttons (background colors are handled by TSKButton now)
      dialog._no_button.render(no_button_rect)
      dialog._yes_button.render(yes_button_rect)

    return dialog.result
