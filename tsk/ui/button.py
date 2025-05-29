# tsk/ui/button.py

from typing import Callable, List, Dict, Any
import platform

import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.widgets.button import gui_button, Button as OpenPilotButton, ButtonStyle
from tsk.ui.layout import Theme


class Button:
  """Represents a button with text labels and an action."""

  def __init__(self, action: Callable[[], None], labels: List[Dict[str, Any]], width: int, height: int, x: int, y: int,
               font_size: int):
    """
    Initializes a Button object.

    Args:
      key: The key associated with the button.
      action: The function to be called when the button is pressed.
      labels: A list of dictionaries containing text and offset information for the button labels.
      width: The width of the button.
      height: The height of the button.
      x: The x-coordinate of the button.
      y: The y-coordinate of the button.
      font_size: The font size of the button labels.
    """
    self.action: Callable[[], None] = action
    self.labels: List[Dict[str, Any]] = labels
    self.width: int = width
    self.height: int = height
    self.x: int = x
    self.y: int = y
    self.font_size: int = font_size
    self.last_pressed_time: float = 0.0
    self.debounce_delay: float = 0.2  # seconds

    # ADDED: Platform detection for Widget system
    self.use_widget = platform.system() == "Linux"
    if self.use_widget:
      self._widget = OpenPilotButton(
        text="",
        click_callback=self._on_click,
        button_style=ButtonStyle.NORMAL,
        font_size=1,
      )

  def _on_click(self):
    """Handle Widget click."""
    current_time = rl.get_time()
    if current_time - self.last_pressed_time > self.debounce_delay:
      self.action()
      self.last_pressed_time = current_time

  def render(self) -> None:
    """Renders the button."""
    rect = rl.Rectangle(self.x, self.y, self.width, self.height)

    if self.use_widget:
      # Linux: Use Widget system
      self._widget.render(rect)
      # Draw TSKM background over Widget
      rl.draw_rectangle_rounded(rect, 0.1, 10, rl.Color(51, 51, 51, 255))
    else:
      # macOS: Use gui_button
      current_time = rl.get_time()
      if gui_button(rect, ""):
        if current_time - self.last_pressed_time > self.debounce_delay:
          self.action()
          self.last_pressed_time = current_time

    self._draw_labels()

  def _draw_labels(self) -> None:
    """Draws the labels on the button."""
    for label_data in self.labels:
      rl.draw_text_ex(
        gui_app.font(),
        label_data["text"],
        rl.Vector2(self.x + label_data["x_offset"], self.y + label_data["y_offset"]),
        self.font_size,
        1.0,
        Theme.brighten_color(rl.Color(100, 100, 100, 255), Theme.brighten_amount),  # Use the brightened color here
      )
