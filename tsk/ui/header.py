# tsk/ui/widgets/header.py
"""
TSK Header widget with navigation and status display.

Pure Widget architecture - NO platform detection needed.
"""

from typing import Optional
import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.ui import TSKWidget
from tsk.ui.button import TSKButton
from tsk.ui.layout import Theme
from tsk.common.key_file_manager import KeyFileManager


class TSKHeader(TSKWidget):
  """
  Header widget for TSK Manager.

  Displays:
  - Title with current menu name
  - Navigation buttons (left/right based on current menu)
  - Key installation status

  NO platform detection needed - Widget handles everything.
  """

  def __init__(self):
    super().__init__()
    self.key_manager = KeyFileManager()
    self._current_menu = Theme.menu_tools
    self._nav_result = None

    # Create navigation buttons (TSKButton handles events automatically)
    self._nav_left = TSKButton(
      labels=[
        {"text": "< Tools", "x_offset": 10, "y_offset": 20},
        {"text": "< Menu", "x_offset": 10, "y_offset": 90},
      ],
      click_callback=lambda: self._set_nav(Theme.menu_tools),
      font_size=Theme.nav_button_font_size,
      multi_line=True
    )

    self._nav_right = TSKButton(
      labels=[
        {"text": "Reboot >", "x_offset": 10, "y_offset": 20},
        {"text": "Menu >", "x_offset": 55, "y_offset": 90},
      ],
      click_callback=lambda: self._set_nav(Theme.menu_reboot),
      font_size=Theme.nav_button_font_size,
      multi_line=True
    )

  def _set_nav(self, menu_id: int):
    """Set navigation result when button is clicked."""
    self._nav_result = menu_id

  def get_height(self) -> float:
    """Calculate the total height of the header."""
    title_height = rl.measure_text_ex(
      gui_app.font(),
      "TSK Manager: ",
      Theme.title_font_size,
      0
    ).y * 1.5
    key_status_height = Theme.key_status_font_size * 1.5
    return title_height + key_status_height

  def set_current_menu(self, menu_id: int):
    """Update the current menu for display."""
    self._current_menu = menu_id

  def _render(self, rect: rl.Rectangle) -> Optional[int]:
    """
    Render the header.

    Returns:
        New menu ID if navigation button was clicked, None otherwise
    """
    title_height = rl.measure_text_ex(
      gui_app.font(),
      "TSK Manager: ",
      Theme.title_font_size,
      0
    ).y * 1.5
    key_status_height = Theme.key_status_font_size * 1.5

    # Draw title strip
    title_rect = rl.Rectangle(rect.x, rect.y, rect.width, title_height)
    rl.draw_rectangle_rec(title_rect, Theme.title_bg_color)
    self._draw_title(title_rect)

    # Draw key status strip
    key_status_y = rect.y + title_height
    key_status_rect = rl.Rectangle(
      rect.x,
      key_status_y,
      rect.width,
      key_status_height
    )
    rl.draw_rectangle_rec(key_status_rect, Theme.key_bg_color)
    self._draw_key_status(key_status_rect)

    # Draw navigation buttons
    self._nav_result = None
    self._draw_navigation_buttons(rect, title_height, key_status_height)

    return self._nav_result

  def _draw_title(self, rect: rl.Rectangle):
    """Draw the title text."""
    # Use white text for header title
    title_text_color = Theme.brighten_color(Theme.title_bg_color, Theme.brighten_amount)
    menu_name = Theme.menu_names.get(self._current_menu, "Unknown Menu")
    prefix = "TSK Manager: "

    # Measure and position text
    prefix_size = rl.measure_text_ex(
      gui_app.font(),
      prefix,
      Theme.title_font_size,
      0
    )

    prefix_x = rect.width * Theme.title_prefix_x_offset_percent + Theme.title_x_offset
    menu_name_x = prefix_x + prefix_size.x + 120

    full_text = f"{prefix}{menu_name}"
    full_size = rl.measure_text_ex(
      gui_app.font(),
      full_text,
      Theme.title_font_size,
      0
    )
    text_y = rect.y + (rect.height - full_size.y) / 2

    # Draw prefix
    rl.draw_text_ex(
      gui_app.font(),
      prefix,
      rl.Vector2(prefix_x, text_y),
      Theme.title_font_size,
      0,
      title_text_color
    )

    # Draw menu name
    rl.draw_text_ex(
      gui_app.font(),
      menu_name,
      rl.Vector2(menu_name_x, text_y),
      Theme.title_font_size,
      0,
      title_text_color
    )

  def _draw_key_status(self, rect: rl.Rectangle):
    """Draw the key installation status."""
    if self.key_manager.installed_key:
      status_text = f"Key installed: {self.key_manager.installed_key}"
    else:
      status_text = "Key not installed"

    text_size = rl.measure_text_ex(
      gui_app.font(),
      status_text,
      Theme.key_status_font_size,
      0
    )

    # Center text
    text_x = rect.x + (rect.width - text_size.x) / 2 - 100
    text_y = rect.y + (rect.height - text_size.y) / 2

    rl.draw_text_ex(
      gui_app.font(),
      status_text,
      rl.Vector2(text_x, text_y),
      Theme.key_status_font_size,
      0,
      Theme.key_text_color
    )

  def _draw_navigation_buttons(
          self,
          rect: rl.Rectangle,
          title_height: float,
          key_status_height: float
  ):
    """Draw navigation buttons overlapping the header."""
    # Calculate button dimensions
    button_height = title_height + key_status_height

    # Calculate button width based on text
    left_text_size = rl.measure_text_ex(
      gui_app.font(),
      Theme.nav_button_text_left.replace('\\n', ' '),
      Theme.nav_button_font_size,
      0
    )
    right_text_size = rl.measure_text_ex(
      gui_app.font(),
      Theme.nav_button_text_right.replace('\\n', ' '),
      Theme.nav_button_font_size,
      0
    )
    button_width = max(left_text_size.x, right_text_size.x) + 70

    # Show appropriate button based on current menu
    if self._current_menu == Theme.menu_reboot:
      # Show left button (back to tools)
      left_rect = rl.Rectangle(rect.x, rect.y, button_width, button_height)
      self._nav_left.render(left_rect)
    elif self._current_menu == Theme.menu_tools:
      # Show right button (go to reboot)
      right_rect = rl.Rectangle(
        rect.x + rect.width - button_width,
        rect.y,
        button_width,
        button_height
      )
      self._nav_right.render(right_rect)
