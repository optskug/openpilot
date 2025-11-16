# tsk/c3/tools_menu/ui.py
"""
Tools Menu UI for TSK Manager.

Pure Widget architecture - NO platform detection needed.
"""

import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.c3.tools_menu.actions import tsk_extractor_action, tsk_uninstaller_action, tsk_guide_action
from tsk.c3.tools_menu.keyboard import KeyboardDialog
from tsk.c3.ui.button import TSKButton
from tsk.c3.ui.layout import Layout, Theme
from tsk.common.widget import TSKWidget


class ToolsMenuUI(TSKWidget):
  """
  Tools Menu widget with buttons for TSK tools.

  NO platform detection - pure Widget architecture.
  """

  def __init__(self):
    super().__init__()

    # Buttons will be created on first render when we have the actual rect
    self._buttons_created = False
    self.extractor_button = None
    self.keyboard_button = None
    self.uninstaller_button = None
    self.guide_button = None

  def _create_buttons(self, rect: rl.Rectangle, header_height: float):
    """Create buttons with proper positioning based on available space."""
    # rect is already the menu area (header subtracted), so pass 0 for header_height
    button_height = Layout.calculate_button_dimensions(rect.height, 0)
    start_x, start_y = Layout.calculate_button_positions(rect, 3)

    button1_x = start_x
    button2_x = start_x + 600 + 80
    button3_x = start_x + 2 * (600 + 80)
    button_y = start_y


    # Create the three main buttons with custom label positioning
    self.extractor_button = TSKButton(
      labels=[{"text": "TSK Extractor", "x_offset": 55, "y_offset": (button_height / 2) - 45}],
      click_callback=tsk_extractor_action,
      font_size=72,
      width=600,
      height=button_height
    )
    self._extractor_rect = rl.Rectangle(button1_x, button_y, 600, button_height)

    self.keyboard_button = TSKButton(
      labels=[{"text": "TSK Keyboard", "x_offset": 45, "y_offset": (button_height / 2) - 45}],
      click_callback=KeyboardDialog.ask,
      font_size=72,
      width=600,
      height=button_height
    )
    self._keyboard_rect = rl.Rectangle(button2_x, button_y, 600, button_height)

    self.uninstaller_button = TSKButton(
      labels=[{"text": "TSK Uninstaller", "x_offset": 25, "y_offset": (button_height / 2) - 45}],
      click_callback=tsk_uninstaller_action,
      font_size=72,
      width=600,
      height=button_height
    )
    self._uninstaller_rect = rl.Rectangle(button3_x, button_y, 600, button_height)

    # Create the "Tell me what to do next" guide button
    guide_button_width = 3 * 600 + 2 * 80
    guide_button_height = 200
    guide_button_x = (rect.width - guide_button_width) / 2 + rect.x
    guide_button_y = button_y + button_height + 80

    # Calculate centered text offset for guide button
    guide_text = "Tell me what to do next"
    text_size = rl.measure_text_ex(gui_app.font(), guide_text, 72, 1.0)
    # This is so hand-crafted it might as well be a magic number. Oh well.
    guide_x_offset = ((guide_button_width - text_size.x) / 2) - 80

    self.guide_button = TSKButton(
      labels=[{"text": guide_text, "x_offset": guide_x_offset, "y_offset": 60}],
      click_callback=tsk_guide_action,
      font_size=72,
      width=guide_button_width,
      height=guide_button_height
    )
    self._guide_rect = rl.Rectangle(guide_button_x, guide_button_y, guide_button_width, guide_button_height)

    self._buttons_created = True

  def render_with_header_height(self, rect: rl.Rectangle, header_height: float):
    """Render the Tools Menu with the actual header height."""
    # Create buttons on first render
    if not self._buttons_created:
      self._create_buttons(rect, header_height)

    # Render all buttons
    if self.extractor_button:
      self.extractor_button.render(self._extractor_rect)
    if self.keyboard_button:
      self.keyboard_button.render(self._keyboard_rect)
    if self.uninstaller_button:
      self.uninstaller_button.render(self._uninstaller_rect)
    if self.guide_button:
      self.guide_button.render(self._guide_rect)

    return None

  def _render(self, rect: rl.Rectangle):
    """Render the Tools Menu (fallback if called directly)."""
    # Estimate header height if not provided
    header_height = Theme.title_font_size * 1.5 + Theme.key_status_font_size * 1.5
    return self.render_with_header_height(rect, header_height)
