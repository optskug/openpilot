# tsk/c3/ui/measure_text.py
"""
Text measurement that matches actual rendered size.

openpilot patches rl.draw_text_ex to multiply font_size by FONT_SCALE,
but rl.measure_text_ex is NOT patched. This causes centering calculations
to underreport text width, pushing centered text to the right.

This function measures at the scaled size so centering is correct.
"""

import pyray as rl

from openpilot.system.ui.lib.application import gui_app, FONT_SCALE


def measure_text(text, font_size):
  return rl.measure_text_ex(gui_app.font(), text, font_size * FONT_SCALE, 0)
