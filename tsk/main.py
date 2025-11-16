#!/usr/bin/env python3
# tsk/main.py
"""
TSK Manager main application.

Pure Widget architecture - NO platform detection needed.
"""

import sys
import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.ui import TSKWidget
from tsk.ui.header import TSKHeader
from tsk.ui.layout import Theme
from tsk.tools_menu.ui import ToolsMenuUI
from tsk.reboot_menu.ui import RebootMenuUI
from tsk.common.env import is_calvins_c3x


class TSKManager(TSKWidget):
  """
  Main TSK Manager application widget.

  This is the top-level widget that manages:
  - Header with navigation
  - Menu switching
  - Overall layout

  NO platform detection needed - everything is Widget-based.
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


def setup_environment():
  """Perform initial environment setup, such as enabling SSH."""
  if is_calvins_c3x():
    with open("/data/params/d/GithubUsername", "w") as f:
      f.write("calvinpark")
    with open("/data/params/d/GithubSshKeys", "w") as f:
      f.write("ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQD30Dz8yY3n1DchzsPbuuWMXMBtyeW2Yh5aOjrjLSvUBjqs9OoPrPfOMAPiaKqE6EfEcjV90He9A6q7OywTy5kTD6JsjjoULJKHiGbDdQlclXE2fO/wTnmxPO9yjdDJqiFrPsSGbT/4R78TVUUkEwD+6DcDGtJd7hHQ/GQCWn78kZ/UsZqcukGjhuwI98gOnIOmX3ui2W6/2NrP3IH7GJWnIvDIHafHYwnRkNU7WQ5zyiUw2GX65dTrXt0pDpX/nYp0qjwORf91DTZCg6fimdUo2WAmhYXnQb66IKESpNVfIVA8L0PRNkSepc3RARX0bPgqYGj6TLy9s87UT11mq/ASuIo9IVYWt6okYvloQcwrX6uxKsGutXouXDraxP648s1ErM6BC3tOOagay19cZdQl53k0CZbkIXODlpM/QaW7MdagH7PVzlGGIuHohDAe3M/ltJjRmRfdj89cCGusBlFB5RuLZpzYskp353NZ1qxhL086Mfyg0bBdDK+CGLJ7bY0=\n"
              "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAILXx7npi7/QYSOu2Z0Bhldtey4L2nxEyZKYQY/BIHdak")
    with open("/data/params/d/SshEnabled", "w") as f:
      f.write("1")
    with open("/data/params/d/HasAcceptedTerms", "w") as f:
      f.write("2")
    with open("/data/params/d/CompletedTrainingVersion", "w") as f:
      f.write("0.2.0")


def main():
  """Main function to initialize and run the TSK Manager."""
  setup_environment()

  gui_app.init_window("TSK Manager")
  tskm = TSKManager()

  for _ in gui_app.render():
    tskm.render(rl.Rectangle(0, 0, gui_app.width, gui_app.height))

  rl.close_window()
  sys.exit(0)


if __name__ == "__main__":
  main()
