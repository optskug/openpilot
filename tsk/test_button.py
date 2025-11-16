#!/usr/bin/env python3
# tsk/test_button.py
"""
Simple test script to verify TSKButton works correctly.
Tests both single-line and multi-line buttons with the Widget system.
"""

import sys
import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.ui.button import TSKButton


def main():
  """Test TSKButton widget."""

  print("Initializing TSKButton test...")
  gui_app.init_window("TSK Button Test")

  # Test 1: Simple string button (auto-centered)
  button1 = TSKButton(
    labels="Click Me!",
    click_callback=lambda: print("Button 1 clicked!"),
    font_size=80,
    width=600,
    height=200
  )

  # Test 2: Multi-line button
  button2 = TSKButton(
    labels="< Tools\n< Menu",
    click_callback=lambda: print("Button 2 clicked!"),
    font_size=80,
    width=400,
    height=200,
    multi_line=True
  )

  # Test 3: Custom labels with offsets (legacy format)
  button3 = TSKButton(
    labels=[
      {'text': 'Custom', 'x_offset': 50, 'y_offset': 50},
      {'text': 'Labels', 'x_offset': 50, 'y_offset': 120}
    ],
    click_callback=lambda: print("Button 3 clicked!"),
    font_size=70,
    width=600,
    height=200
  )

  print("Test window opened. Click buttons to test.")
  print("Press ESC or close window to exit.")

  # Render loop
  for _ in gui_app.render():
    rl.clear_background(rl.BLACK)

    # Draw title
    rl.draw_text("TSK Button Widget Test", 50, 50, 40, rl.WHITE)
    rl.draw_text("(Pure Widget architecture - no platform detection)", 50, 100, 30, rl.GRAY)

    # Render buttons
    button1.render(rl.Rectangle(100, 200, 600, 200))
    button2.render(rl.Rectangle(100, 450, 400, 200))
    button3.render(rl.Rectangle(100, 700, 600, 200))

  rl.close_window()
  print("Test completed successfully!")
  sys.exit(0)


if __name__ == "__main__":
  main()
