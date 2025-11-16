# tsk/c3/ui/render_loop.py
"""
Forked render loop for C3X, decoupled from gui_app.render().

WHY THIS EXISTS:
  gui_app.render() has been the #1 source of breakage across openpilot
  versions (120 commits between 2025-01 and 2026-03). Key breaking changes:
    - v0.10.x: Added modal overlay yield (should_render_main)
    - v0.11.x: Added rl_push_matrix/rl_scalef for SCALE support,
               removed modal overlay in favor of nav stack
  C3X dialogs use blocking render loops (OkayDialog.ask(), YesNoDialog.ask())
  that call gui_app.render() inside the main gui_app.render() loop. This
  nesting applies the scale matrix twice, shrinking the UI to 1/16th size.

  This function provides a minimal render loop using pure raylib calls.
  It handles mouse events for the Widget system but does NOT apply scale
  matrices, making it safe to nest (dialogs inside main loop).

USAGE:
  from tsk.c3.ui.render_loop import render_loop
  for _ in render_loop():
      widget.render(rect)
"""

import pyray as rl

from openpilot.system.ui.lib.application import gui_app, PC


def render_loop():
    while not rl.window_should_close():
        if PC:
            gui_app._mouse._handle_mouse_event()
        gui_app._mouse_events = gui_app._mouse.get_events()
        if gui_app._mouse_events:
            gui_app._last_mouse_event = gui_app._mouse_events[-1]

        rl.begin_drawing()
        rl.clear_background(rl.BLACK)
        yield True
        rl.end_drawing()
