# tsk/common/widget.py
"""
TSK Widget abstraction layer.

This module provides TSK-specific widgets that extend openpilot's Widget system.
By creating this abstraction layer, we insulate the TSK application from changes
in the underlying openpilot UI library.
"""

from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.widgets.scroller import _Scroller

__all__ = ['TSKWidget', 'Scroller']


# ============================================================================
# Scroller factory function
# ============================================================================
# This replaces the direct import of openpilot's Scroller widget.
#
# WHY: openpilot's Scroller API changes frequently between releases.
#   - In v0.10.x: Scroller(items, horizontal=True, pad_start=10, pad_end=10)
#   - In v0.11.x: Scroller split into Scroller (wrapper) and _Scroller (impl).
#     The wrapper no longer accepts items in the constructor, removed pad_start/
#     pad_end (now just pad), and doesn't expose scroll_panel or
#     set_scrolling_enabled.
#
# This function wraps _Scroller (the actual implementation) so that:
#   1. TSK code can call Scroller(items, ...) like a normal constructor
#   2. The returned object has scroll_panel, set_scrolling_enabled, etc.
#   3. When comma changes the API again, we only fix this one place
#
# USAGE: from tsk.common.widget import Scroller
#   scroller = Scroller([widget1, widget2], horizontal=True, pad=10)
#   scroller.scroll_panel.get_offset()
#   scroller.set_scrolling_enabled(True)
# ============================================================================
def Scroller(items, **kwargs):
  return _Scroller(items, **kwargs)


class TSKWidget(Widget):
  """
  Base class for all TSK widgets.

  This extends openpilot's Widget class and provides TSK-specific
  functionality and customization. All TSK UI components should
  extend this class instead of using OpenPilotWidget directly.

  Benefits:
  - Isolation from openpilot UI changes
  - TSK-specific features can be added here
  - Consistent behavior across all TSK widgets
  - Easier testing and mocking
  """

  def __init__(self):
    super().__init__()
    # TSK-specific initialization can go here
    # For example: logging, analytics, custom state management
