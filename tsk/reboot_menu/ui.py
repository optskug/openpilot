# tsk/reboot_menu/ui.py
"""
Reboot Menu UI for TSK Manager.

Pure Widget architecture - NO platform detection needed.
"""

import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.common.env import RECOMMENDED_OP_USER, RECOMMENDED_OP_BRANCH, ALTERNATE_OP_USER, ALTERNATE_OP_BRANCH
from tsk.reboot_menu.actions import Rebooter
from tsk.ui import TSKWidget
from tsk.ui.button import TSKButton
from tsk.ui.layout import Layout, Theme


class RebootMenuUI(TSKWidget):
  """
  Reboot Menu widget with buttons for reboot actions.

  NO platform detection - pure Widget architecture.
  """

  def __init__(self):
    super().__init__()
    self.rebooter = Rebooter()

    # Buttons will be created on first render when we have the actual rect
    self._buttons_created = False
    self.recommended_button = None
    self.alternate_button = None
    self.bail_button = None
    self.retry_button = None

  def _create_buttons(self, rect: rl.Rectangle, header_height: float):
    """Create buttons with proper positioning based on available space."""
    # rect is already the menu area (header subtracted), so pass 0 for header_height
    button_height = Layout.calculate_button_dimensions(rect.height, 0)
    start_x, start_y = Layout.calculate_button_positions(rect, 3)

    button1_x = start_x
    button2_x = start_x + 600 + 80
    button3_x = start_x + 2 * (600 + 80)
    button_y = start_y

    # Create the three main reboot option buttons
    self.recommended_button = TSKButton(
      labels=[
        {"text": "Install", "x_offset": 70, "y_offset": 80},
        {"text": f"{RECOMMENDED_OP_USER}/", "x_offset": 70, "y_offset": 180},
        {"text": f"{RECOMMENDED_OP_BRANCH}", "x_offset": 70, "y_offset": 280},
      ],
      click_callback=self.rebooter.recommended_action,
      font_size=72,
      width=600,
      height=button_height
    )
    self._recommended_rect = rl.Rectangle(button1_x, button_y, 600, button_height)

    self.alternate_button = TSKButton(
      labels=[
        {"text": "Install", "x_offset": 70, "y_offset": 80},
        {"text": f"{ALTERNATE_OP_USER}/", "x_offset": 70, "y_offset": 180},
        {"text": f"{ALTERNATE_OP_BRANCH}", "x_offset": 70, "y_offset": 280},
      ],
      click_callback=self.rebooter.alternate_action,
      font_size=72,
      width=600,
      height=button_height
    )
    self._alternate_rect = rl.Rectangle(button2_x, button_y, 600, button_height)

    self.bail_button = TSKButton(
      labels=[
        {"text": "Install a", "x_offset": 70, "y_offset": 80},
        {"text": "different", "x_offset": 70, "y_offset": 180},
        {"text": "fork/branch", "x_offset": 70, "y_offset": 280},
      ],
      click_callback=self.rebooter.bail_action,
      font_size=72,
      width=600,
      height=button_height
    )
    self._bail_rect = rl.Rectangle(button3_x, button_y, 600, button_height)

    # Create the "Retry" button
    retry_button_width = 3 * 600 + 2 * 80
    retry_button_height = 200
    retry_button_x = (rect.width - retry_button_width) / 2 + rect.x
    retry_button_y = button_y + button_height + 80

    # Calculate centered text offset for retry button
    retry_text = "Reboot to try again"
    text_size = rl.measure_text_ex(gui_app.font(), retry_text, 90, 1.0)
    retry_x_offset = (retry_button_width - text_size.x) / 2

    self.retry_button = TSKButton(
      labels=[{"text": retry_text, "x_offset": retry_x_offset, "y_offset": 60}],
      click_callback=self.rebooter.retry_action,
      font_size=72,
      width=retry_button_width,
      height=retry_button_height
    )
    self._retry_rect = rl.Rectangle(retry_button_x, retry_button_y, retry_button_width, retry_button_height)

    self._buttons_created = True

  def render_with_header_height(self, rect: rl.Rectangle, header_height: float):
    """Render the Reboot Menu with the actual header height."""
    # Create buttons on first render
    if not self._buttons_created:
      self._create_buttons(rect, header_height)

    # Render all buttons
    if self.recommended_button:
      self.recommended_button.render(self._recommended_rect)
    if self.alternate_button:
      self.alternate_button.render(self._alternate_rect)
    if self.bail_button:
      self.bail_button.render(self._bail_rect)
    if self.retry_button:
      self.retry_button.render(self._retry_rect)

    return None

  def _render(self, rect: rl.Rectangle):
    """Render the Reboot Menu (fallback if called directly)."""
    # Estimate header height if not provided
    header_height = Theme.title_font_size * 1.5 + Theme.key_status_font_size * 1.5
    return self.render_with_header_height(rect, header_height)
