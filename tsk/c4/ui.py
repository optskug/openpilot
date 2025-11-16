from typing import Callable

import pyray as rl

from openpilot.common.filter_simple import BounceFilter
from openpilot.selfdrive.ui.mici.widgets.dialog import BigDialogBase
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.system.ui.lib.wrap_text import wrap_text
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.widgets.label import UnifiedLabel
from tsk.common.widget import Scroller


class Layout:
  # Button dimensions
  button_width = 240
  button_height = 140

  # Font sizes
  tools_row_button_font_size = 38
  reboot_row_button_font_size = 35

  # Scroller configuration
  scroller_spacing = 10
  scroller_padding = 10

  # Banner
  banner_height = 50


class ScalableBigButton(Widget):
  """
  Button that uses BigButton graphics but scales to any size.
  """
  def __init__(self,
               text: str,
               click_callback: Callable = None,
               font_size: int = Layout.tools_row_button_font_size,
               text_offset: tuple[int, int] = (15, 15),
               button_width = Layout.button_width,
               button_height = Layout.button_height,
               ):
    super().__init__()
    self._text = text
    self._font_size = font_size
    self._text_offset = text_offset  # (x, y) offset from top-left of button
    self.set_click_callback(click_callback)

    # Load BigButton textures
    self._txt_default_bg = gui_app.texture("icons_mici/buttons/button_rectangle.png", 402, 180)
    self._txt_pressed_bg = gui_app.texture("icons_mici/buttons/button_rectangle_pressed.png", 402, 180)

    # Scale animation
    self._scale_filter = BounceFilter(1.0, 0.1, 1 / gui_app.target_fps)

    # Label for text
    self._label = UnifiedLabel(
      text,
      font_size=font_size,
      font_weight=FontWeight.BOLD,
      text_color=rl.WHITE,
      alignment_vertical=rl.GuiTextAlignmentVertical.TEXT_ALIGN_TOP,
      wrap_text=True
    )

    self.set_rect(rl.Rectangle(0, 0, button_width, button_height))

  def _render(self, rect: rl.Rectangle):
    """Render the button with scaled BigButton graphics."""
    # Choose texture based on press state
    txt_bg = self._txt_pressed_bg if self.is_pressed else self._txt_default_bg

    # Scale animation
    scale = self._scale_filter.update(1.07 if self.is_pressed else 1.0)

    # Calculate scaled position (center the scaled button)
    scaled_width = rect.width * scale
    scaled_height = rect.height * scale
    btn_x = rect.x + (rect.width - scaled_width) / 2
    btn_y = rect.y + (rect.height - scaled_height) / 2

    # Draw background texture scaled to button size
    source_rect = rl.Rectangle(0, 0, self._txt_default_bg.width, self._txt_default_bg.height)
    dest_rect = rl.Rectangle(btn_x, btn_y, scaled_width, scaled_height)
    rl.draw_texture_pro(txt_bg, source_rect, dest_rect, rl.Vector2(0, 0), 0, rl.WHITE)

    # Draw text at specified offset from button top-left
    text_x = rect.x + self._text_offset[0]
    text_y = rect.y + self._text_offset[1]
    label_rect = rl.Rectangle(text_x, text_y, int(rect.width - self._text_offset[0] * 2), int(rect.height - self._text_offset[1]))
    self._label.render(label_rect)

    return True


class ScrollableBigDialog(BigDialogBase):
  """
  A BigDialog variant that supports scrolling for long text content.

  Features:
  - Optional title (no space wasted if title is empty string or None)
  - Configurable alignment for title and description (left or center)
  - Configurable font sizes for title and description
  - Scrollable description area

  Usage:
    dialog = ScrollableBigDialog(
      title="Title",
      description="Very long text that needs scrolling...",
      title_font_size=45,
      title_alignment=rl.GuiTextAlignment.TEXT_ALIGN_CENTER,
      desc_font_size=25,
      desc_alignment=rl.GuiTextAlignment.TEXT_ALIGN_LEFT
    )
    gui_app.push_widget(dialog)
  """
  PADDING = 20

  def __init__(self,
               title: str = "",
               description: str = "",
               title_font_size: int = 45,
               title_alignment: int = rl.GuiTextAlignment.TEXT_ALIGN_CENTER,
               desc_font_size: int = 45,
               desc_alignment: int = rl.GuiTextAlignment.TEXT_ALIGN_LEFT,
               scroll_to_bottom: bool = False):
    super().__init__()
    self._title = title
    self._description = description
    self._title_font_size = title_font_size
    self._title_alignment = title_alignment
    self._desc_font_size = desc_font_size
    self._desc_alignment = desc_alignment
    self._scroll_to_bottom = scroll_to_bottom
    self._initial_scroll_done = False

    # Create label for description text
    max_width = self._rect.width - self.PADDING * 2

    self._desc_label = UnifiedLabel(
      description,
      font_size=desc_font_size,
      text_color=rl.WHITE,
      font_weight=FontWeight.MEDIUM,
      alignment=desc_alignment
    )

    # Create scroller for the description with scroll indicator
    self._scroller = Scroller(
      [self._desc_label],
      horizontal=False,
      snap_items=False,
      spacing=0,
      pad=10
    )
  def _bottom_reserved_height(self) -> float:
    """Height reserved at the bottom for subclass widgets (e.g., slider). Override in subclasses."""
    return 0

  def _back_enabled(self) -> bool:
    """Only allow swipe-to-dismiss when scroller is at the top."""
    return self._scroller.scroll_panel.get_offset() >= -20

  def _render(self, _):
    super()._render(_)

    # Calculate available width
    max_width = self._rect.width - self.PADDING * 2

    # Draw title (if provided and not empty)
    title_bottom = self._rect.y + self.PADDING
    if self._title:
      title_wrapped = '\n'.join(wrap_text(gui_app.font(FontWeight.BOLD), self._title, self._title_font_size, int(max_width)))
      title_size = measure_text_cached(gui_app.font(FontWeight.BOLD), title_wrapped, self._title_font_size)
      title_rect = rl.Rectangle(
        int(self._rect.x + self.PADDING),
        int(self._rect.y + self.PADDING),
        int(max_width),
        int(title_size.y)
      )

      from openpilot.system.ui.widgets.label import gui_label
      gui_label(title_rect, title_wrapped, self._title_font_size, font_weight=FontWeight.BOLD,
                alignment=self._title_alignment)

      title_bottom = title_rect.y + title_rect.height + self.PADDING

    # Scroller uses full width so wide items (e.g., slider) aren't clipped.
    # Text padding is handled separately via set_max_width.
    scroller_rect = rl.Rectangle(
      int(self._rect.x),
      int(title_bottom),
      int(self._rect.width),
      int(self._rect.y + self._rect.height - title_bottom - self.PADDING - self._bottom_reserved_height())
    )

    # Update label width for proper text wrapping
    self._desc_label.set_max_width(int(max_width))

    # Check if content is scrollable
    content_height = self._desc_label.get_content_height(int(max_width))
    is_scrollable = content_height > scroller_rect.height

    # Disable scrolling if content fits in viewport
    self._scroller.set_scrolling_enabled(is_scrollable)

    # Scroll to bottom on first render if flag is set
    if self._scroll_to_bottom and not self._initial_scroll_done and is_scrollable:
      scrollable_height = content_height - scroller_rect.height
      self._scroller.scroll_panel.set_offset(-scrollable_height)
      self._initial_scroll_done = True

    # Render the scroller
    self._scroller.render(scroller_rect)

    # Draw scroll indicator if content is scrollable
    if is_scrollable:
      scroll_offset = self._scroller.scroll_panel.get_offset()
      scrollable_height = content_height - scroller_rect.height
      scroll_progress = -scroll_offset / scrollable_height if scrollable_height > 0 else 0
      scroll_progress = max(0, min(1, scroll_progress))

      # Draw a thin rounded scrollbar on the right edge
      indicator_height = max(20, scroller_rect.height * (scroller_rect.height / content_height))
      indicator_y = scroller_rect.y + scroll_progress * (scroller_rect.height - indicator_height)
      indicator_rect = rl.Rectangle(self._rect.x + self._rect.width - 12, indicator_y, 8, indicator_height)
      rl.draw_rectangle_rounded(indicator_rect, 1.0, 4, rl.Color(255, 255, 255, 178))

    return


# ============================================================================
# ScrollableConfirmDialog
# ============================================================================
# A full-screen dialog with scrollable text and a confirm button that
# appears only after the user scrolls to the bottom of the content.
#
# PURPOSE:
#   Used for sensitive/destructive operations (uninstall key, reboot to a
#   different fork, etc.) where the user needs to:
#     1. Read important information (e.g., which key is installed, what
#        will happen). This info can be many pages long and is scrollable.
#     2. Confirm by tapping a button that only appears after reading.
#   Swipe down to cancel (standard NavWidget behavior).
#
# WHY THIS EXISTS:
#   openpilot's upstream BigConfirmationDialog uses a slider that's too
#   large for C4's 240px screen, and causes gesture conflicts when placed
#   inside a scroller. This simpler approach uses a confirm button that
#   appears at the bottom-right only after the user scrolls to the bottom.
#
# BEHAVIOR:
#   1. Full screen is used for scrollable description text
#   2. Confirm button appears only when bottom of text is reached
#   3. Scrolling back up hides the button
#   4. Swipe down from top to cancel
#
# USAGE:
#   dialog = ScrollableConfirmDialog(
#     description="Key installed: ABCD1234...\n\nThis will remove the key.",
#     confirm_text="Uninstall",
#     confirm_callback=do_the_thing
#   )
#   gui_app.push_widget(dialog)
# ============================================================================
class ScrollableConfirmDialog(ScrollableBigDialog):
  BUTTON_WIDTH = 100
  BUTTON_HEIGHT = 60
  BUTTON_MARGIN = 10
  BUTTON_FONT_SIZE = 35
  BUTTON_COLOR = rl.Color(20, 120, 20, 255)
  BUTTON_PRESSED_COLOR = rl.Color(30, 160, 30, 255)

  def __init__(self,
               confirm_text: str = "Yes",
               confirm_callback: Callable | None = None,
               **kwargs):
    # Add padding at bottom so text scrolls past the confirm button
    if 'description' in kwargs:
      kwargs['description'] = kwargs['description'] + '\n'
    super().__init__(**kwargs)
    self._confirm_callback = confirm_callback
    self._confirm_text = confirm_text
    self._show_button = False

    # Create confirm button — UnifiedLabel is a concrete Widget with click handling
    self._confirm_button = self._child(UnifiedLabel(
      confirm_text, font_size=self.BUTTON_FONT_SIZE, font_weight=FontWeight.BOLD,
      text_color=rl.WHITE, alignment=rl.GuiTextAlignment.TEXT_ALIGN_CENTER,
      alignment_vertical=rl.GuiTextAlignmentVertical.TEXT_ALIGN_MIDDLE
    ))
    self._confirm_button.set_click_callback(self._on_confirm)
    self._confirm_button.set_enabled(lambda: self._show_button and self.enabled and not self.is_dismissing)

  def _on_confirm(self):
    self.dismiss(self._confirm_callback)

  def _render(self, _):
    super()._render(_)

    # Check if content is scrolled to bottom (or fits on screen without scrolling)
    scroll_offset = self._scroller.scroll_panel.get_offset()
    max_width = self._rect.width - self.PADDING * 2
    content_height = self._desc_label.get_content_height(int(max_width))
    scroller_height = self._rect.height - self.PADDING * 2
    if content_height <= scroller_height:
      at_bottom = True
    else:
      scrollable_height = content_height - scroller_height
      at_bottom = -scroll_offset >= scrollable_height - 20

    self._show_button = at_bottom

    if self._show_button:
      # Draw button at bottom-right
      btn_x = self._rect.x + self._rect.width - self.BUTTON_WIDTH - self.BUTTON_MARGIN
      btn_y = self._rect.y + self._rect.height - self.BUTTON_HEIGHT - self.BUTTON_MARGIN
      btn_rect = rl.Rectangle(btn_x, btn_y, self.BUTTON_WIDTH, self.BUTTON_HEIGHT)

      color = self.BUTTON_PRESSED_COLOR if self._confirm_button.is_pressed else self.BUTTON_COLOR
      rl.draw_rectangle_rounded(btn_rect, 0.3, 10, color)
      self._confirm_button.render(btn_rect)
