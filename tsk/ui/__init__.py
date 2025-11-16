# tsk/ui/widgets/__init__.py
"""
TSK Widget abstraction layer.

This module provides TSK-specific widgets that extend openpilot's Widget system.
By creating this abstraction layer, we insulate the TSK application from changes
in the underlying openpilot UI library.
"""

from openpilot.system.ui.widgets import Widget as OpenPilotWidget

__all__ = ['TSKWidget']


class TSKWidget(OpenPilotWidget):
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
