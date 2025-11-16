#!/usr/bin/env python3
# tsk/main.py
"""
TSK Manager entry point.

Detects device type (C3X vs C4) and loads appropriate GUI.
"""

import sys

import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.common.env import is_calvins_comma


def setup_environment():
  """Perform initial environment setup, such as enabling SSH."""
  if is_calvins_comma():
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

  if gui_app.big_ui():
    # C3X: use forked render loop (see tsk/c3/ui/render_loop.py for why)
    from tsk.c3.tsk_manager import TSKManager
    from tsk.c3.ui.render_loop import render_loop
    tskm = TSKManager()
    for _ in render_loop():
      tskm.render(rl.Rectangle(0, 0, gui_app.width, gui_app.height))
  else:
    # C4: use nav stack — dialogs are pushed as NavWidgets
    from tsk.c4.tsk_manager import TSKManager
    tskm = TSKManager()
    gui_app.push_widget(tskm)
    for _ in gui_app.render():
      pass

  rl.close_window()
  sys.exit(0)


if __name__ == "__main__":
  main()
