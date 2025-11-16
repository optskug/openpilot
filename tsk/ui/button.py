# tsk/ui/widgets/button.py
"""
TSK Button widget.

Provides TSK-styled buttons with automatic event handling through the Widget system.
NO platform detection needed - Widget handles everything cross-platform.
"""

from typing import Callable, List, Dict, Any, Optional
import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.ui import TSKWidget
from tsk.ui.layout import Theme


class TSKButton(TSKWidget):
  """
  TSK-styled button widget.

  Features:
  - TSK-specific styling (dark background, brightened text)
  - Multi-label support with custom positioning
  - Multi-line text support
  - Automatic event handling via Widget system

  NO platform detection - pure Widget architecture.
  """

  def __init__(
          self,
          labels: List[Dict[str, Any]] | str,
          click_callback: Optional[Callable[[], None]] = None,
          font_size: int = 80,
          width: int = 600,
          height: int = 200,
          multi_line: bool = False,
          background_color: Optional[rl.Color] = None,  # ADDED: Custom background color
  ):
    """
    Initialize TSKButton.

    Args:
        labels: Either a list of label dicts with 'text', 'x_offset', 'y_offset',
               or a simple string for single-line text (will be auto-centered)
        click_callback: Function to call when button is clicked
        font_size: Font size for button text
        width: Button width (used for layout calculations)
        height: Button height (used for layout calculations)
        multi_line: If True and labels is a string, split on \\n for multi-line
        background_color: Custom background color (defaults to gray if not provided)
    """
    super().__init__()

    # Store original labels specification
    self._labels_spec = labels
    self._multi_line = multi_line
    self._font_size = font_size
    self._init_width = width
    self._init_height = height

    # Use custom background color if provided, otherwise default gray
    if background_color is not None:
      self._background_color = background_color
    else:
      # Use gui_button-style colors (lighter background, white text)
      self._background_color = rl.Color(75, 75, 75, 255)  # Lighter gray to match gui_button

    self._text_color = rl.Color(240, 240, 240, 255)  # Near-white text

    # Set click callback
    if click_callback:
      self.set_click_callback(click_callback)

  def _calculate_labels(self, width: float, height: float) -> List[Dict[str, Any]]:
    """Calculate label positions based on actual button size."""
    if isinstance(self._labels_spec, str):
      if self._multi_line and '\\n' in self._labels_spec:
        # Multi-line text: split and stack vertically
        lines = self._labels_spec.split('\\n')
        labels = []
        line_height = self._font_size * 1.2
        total_height = len(lines) * line_height
        start_y = (height - total_height) / 2

        for i, line in enumerate(lines):
          text_size = rl.measure_text_ex(gui_app.font(), line, self._font_size, 0)
          x_offset = (width - text_size.x) / 2
          y_offset = start_y + (i * line_height)
          labels.append({
            'text': line,
            'x_offset': x_offset,
            'y_offset': y_offset
          })
        return labels
      else:
        # Single line: center it
        text_size = rl.measure_text_ex(gui_app.font(), self._labels_spec, self._font_size, 0)
        x_offset = (width - text_size.x) / 2
        y_offset = (height - text_size.y) / 2
        return [{
          'text': self._labels_spec,
          'x_offset': x_offset,
          'y_offset': y_offset
        }]
    else:
      # Custom label positioning - return as-is
      return self._labels_spec

  def _render(self, rect: rl.Rectangle):
    """
    Render the TSK button.

    Widget system automatically handles:
    - Mouse/touch events
    - Press state
    - Click callbacks

    We just need to draw the button appearance.
    """
    # Draw button background with rounded corners
    rl.draw_rectangle_rounded(rect, 0.1, 10, self._background_color)

    # Calculate labels based on actual rect size
    labels = self._calculate_labels(rect.width, rect.height)

    # Draw all labels
    for label_data in labels:
      rl.draw_text_ex(
        gui_app.font(),
        label_data['text'],
        rl.Vector2(rect.x + label_data['x_offset'], rect.y + label_data['y_offset']),
        self._font_size,
        1.0,
        self._text_color
      )

    return None
