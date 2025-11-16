# tsk/c3/tsk_manager.py
"""
TSK Manager main application.
"""

import pyray as rl

from tsk.c3.reboot_menu.ui import RebootMenuUI
from tsk.c3.tools_menu.ui import ToolsMenuUI
from tsk.c3.ui.header import TSKHeader
from tsk.c3.ui.layout import Theme
from tsk.common.widget import TSKWidget


class TSKManager(TSKWidget):
  """
  Main TSK Manager application widget for C3X devices.

  This is the top-level widget that manages:
  - Header with navigation
  - Menu switching
  - Overall layout

  For C3X devices only (tici/tizi).
  """

  def __init__(self):
    super().__init__()
    self._current_menu = Theme.menu_tools

    # Create child widgets
    self.header = TSKHeader()
    self.tools_menu = ToolsMenuUI()
    self.reboot_menu = RebootMenuUI()

  def _render(self, rect: rl.Rectangle):
    """Render the TSK Manager UI."""
    # Clear background
    rl.clear_background(rl.BLACK)

    # Render header
    header_height = self.header.get_height()
    header_rect = rl.Rectangle(rect.x, rect.y, rect.width, header_height)

    # Update header's current menu
    self.header.set_current_menu(self._current_menu)

    # Render header and get navigation result
    nav_result = self.header.render(header_rect)
    if nav_result is not None:
      self._current_menu = nav_result

    # Render current menu
    menu_rect = rl.Rectangle(
      rect.x,
      rect.y + header_height,
      rect.width,
      rect.height - header_height
    )

    if self._current_menu == Theme.menu_tools:
      self.tools_menu.render_with_header_height(menu_rect, header_height)
    elif self._current_menu == Theme.menu_reboot:
      self.reboot_menu.render_with_header_height(menu_rect, header_height)

    return True
