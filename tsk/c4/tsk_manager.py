# tsk/c4/tsk_manager.py
"""
TSK Manager main application for C4 (mici) device.

Features:
- Fixed top banner showing key installation status (clickable)
- Vertical scroller with two horizontal scrollers (one for each row of buttons)

Uses custom button with BigButton graphics that scales properly.
"""

import pyray as rl

from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.widgets import Widget
from tsk.common.widget import Scroller
from tsk.c4.menu_0_tools.btn_0_extractor import Extractor
from tsk.c4.menu_0_tools.btn_1_keyboard import Keyboard
from tsk.c4.menu_0_tools.btn_2_uninstaller import Uninstaller
from tsk.c4.menu_0_tools.btn_3_guide import Guide
from tsk.c4.menu_1_reboot.btn_0_recommended import Recommended
from tsk.c4.menu_1_reboot.btn_1_alternate import Alternate
from tsk.c4.menu_1_reboot.btn_2_somethingelse import SomethingElse
from tsk.c4.menu_1_reboot.btn_3_reboot import Reboot
from tsk.c4.ui import Layout, ScrollableBigDialog
from tsk.common.key_file_manager import KeyFileManager
from tsk.common.widget import TSKWidget


class KeyStatusBanner(Widget):
  """
  Top banner showing key installation status.
  Acts as a button - click to see details.
  """
  def __init__(self, key_manager: KeyFileManager):
    super().__init__()
    self._key_manager = key_manager
    self.set_rect(rl.Rectangle(0, 0, gui_app.width, Layout.banner_height))

  def _get_status_text(self) -> str:
    """Get the current key status text."""
    if self._key_manager.installed_key:
      return "Key installed"
    else:
      return "Key not installed"

  def _handle_mouse_release(self, mouse_pos):
    """Handle click on the banner."""
    if self._key_manager.installed_key:
      # Show the installed key
      self._show_installed_key_dialog()
    else:
      # Show instruction to run TSK Extractor
      self._show_no_key_dialog()
    return True

  def _show_no_key_dialog(self):
    """Show dialog when no key is installed."""
    dialog = ScrollableBigDialog(
      description="Run TSK Extractor to get your key"
    )
    gui_app.push_widget(dialog)

  def _show_installed_key_dialog(self):
    """Show dialog displaying the installed key."""
    exploded_key = (
      self._key_manager.installed_key[0:4] + ' ' +
      self._key_manager.installed_key[4:8] + ' ' +
      self._key_manager.installed_key[8:12] + ' ' +
      self._key_manager.installed_key[12:16] + '\n' +
      self._key_manager.installed_key[16:20] + ' ' +
      self._key_manager.installed_key[20:24] + ' ' +
      self._key_manager.installed_key[24:28] + ' ' +
      self._key_manager.installed_key[28:32]
    )
    dialog = ScrollableBigDialog(
      title='Installed Key',
      description=exploded_key
    )
    gui_app.push_widget(dialog)

  def _render(self, rect: rl.Rectangle):
    """Render the key status banner."""
    # Background color: dark gray, slightly lighter when pressed
    bg_color = rl.Color(60, 60, 60, 255) if self.is_pressed else rl.Color(50, 50, 50, 255)
    rl.draw_rectangle_rec(rect, bg_color)

    # Draw status text (centered)
    status_text = self._get_status_text()
    font = gui_app.font(FontWeight.MEDIUM)
    font_size = 28
    text_size = rl.measure_text_ex(font, status_text, font_size, 0)

    text_x = rect.x + (rect.width - text_size.x) / 2
    text_y = rect.y + (rect.height - text_size.y) / 2

    # Color: green if key installed, yellow if not
    text_color = rl.Color(100, 255, 100, 255) if self._key_manager.installed_key else rl.Color(255, 200, 0, 255)

    rl.draw_text_ex(font, status_text, rl.Vector2(text_x, text_y), font_size, 0, text_color)

    # Draw a subtle bottom border
    rl.draw_line(int(rect.x), int(rect.y + rect.height - 1),
                 int(rect.x + rect.width), int(rect.y + rect.height - 1),
                 rl.Color(80, 80, 80, 255))

    return True


class TSKManager(TSKWidget):
  """
  TSK Manager for C4 (mici) device.

  Layout:
  - Fixed top banner: Key status (clickable)
  - Vertical scroller with two horizontal scrollers (one for each row)
  """

  def __init__(self):
    super().__init__()

    # Initialize key manager
    self.key_manager = KeyFileManager()

    # Create top banner (fixed, not scrollable)
    self.key_banner = KeyStatusBanner(self.key_manager)

    # Create two horizontal scrollers
    self.tools_scroller = Scroller(
      [
        Extractor(),
        # Keyboard(),
        Uninstaller(),
        Guide(),
      ],
      horizontal=True,
      snap_items=False,
      spacing=Layout.scroller_spacing,
      pad=Layout.scroller_padding,
      scroll_indicator=False
    )
    self.tools_scroller.set_rect(rl.Rectangle(0, 0, gui_app.width, Layout.button_height))

    self.reboot_scroller = Scroller(
      [
        Recommended(),
        Alternate(),
        SomethingElse(),
        Reboot(),
      ],
      horizontal=True,
      snap_items=False,
      spacing=Layout.scroller_spacing,
      pad=Layout.scroller_padding,
      scroll_indicator=False
    )
    self.reboot_scroller.set_rect(rl.Rectangle(0, 0, gui_app.width, Layout.button_height))

    # Create vertical scroller with the two horizontal scrollers
    self.vertical_scroller = Scroller(
      [self.tools_scroller, self.reboot_scroller],
      horizontal=False,
      snap_items=True,
      spacing=Layout.scroller_spacing,
      pad=Layout.scroller_padding
    )
    # Propagate enabled state so children stop processing input
    # when a dialog is pushed on top (push_widget disables us)
    self.key_banner.set_enabled(lambda: self.enabled)
    self.vertical_scroller.set_enabled(lambda: self.enabled)
    self.tools_scroller.set_enabled(lambda: self.enabled)
    self.reboot_scroller.set_enabled(lambda: self.enabled)

  def _render(self, rect: rl.Rectangle):
    """Render the C4 GUI."""

    # Enable scissor mode for the scroller area to clip overflow
    scroller_rect = rl.Rectangle(
      rect.x,
      rect.y + Layout.banner_height,
      rect.width,
      rect.height - Layout.banner_height
    )

    rl.begin_scissor_mode(int(scroller_rect.x), int(scroller_rect.y),
                          int(scroller_rect.width), int(scroller_rect.height))

    # Render the vertical scroller
    self.vertical_scroller.render(scroller_rect)

    rl.end_scissor_mode()

    # Render the banner AFTER the scroller so it draws on top
    banner_rect = rl.Rectangle(rect.x, rect.y, rect.width, Layout.banner_height)
    self.key_banner.render(banner_rect)

    return True
