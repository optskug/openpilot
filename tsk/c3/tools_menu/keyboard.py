# tsk/c3/tools_menu/keyboard.py
"""
TSK Keyboard Dialog for entering hex keys.

Pure Widget architecture - NO platform detection needed.
"""

import pyray as rl

from openpilot.system.ui.lib.application import gui_app
from tsk.common.key_file_manager import KeyFileManager
from tsk.c3.ui.button import TSKButton
from tsk.c3.ui.measure_text import measure_text
from tsk.c3.ui.render_loop import render_loop


class KeyboardDialog:
  """
  Full-screen keyboard dialog for entering hex keys.

  NO platform detection - pure Widget architecture.
  """

  def __init__(self):
    self.key_file_manager = KeyFileManager()
    self.key_status_text = "Key not installed"
    self.input_text = ""
    self.max_input_length = 32
    self.show_install_button = False
    self.install_success = False
    self.dialog_open = True

    # Font and Color Definitions
    self.font_size = 70
    self.key_status_font_size = 70
    self.keyboard_bg_color = rl.Color(51, 51, 51, 255)
    self.keyboard_border_color = rl.BLACK
    self.keyboard_border_thickness = 4
    self.x_button_text = " X "
    self.x_button_text_color = rl.Color(150, 150, 150, 255)
    self.input_box_bg_color = rl.BLACK
    self.input_box_border_color = rl.WHITE
    self.input_text_color_1 = rl.Color(120, 120, 120, 255)
    self.input_text_color_2 = rl.DARKGRAY

    # Calculate Input Box Dimensions
    widest_char = max("0123456789abcdef", key=lambda c: measure_text(c, self.font_size).x)
    self.char_width = measure_text(widest_char, self.font_size).x
    self.char_spacing = 5
    self.input_box_width = (self.char_width + self.char_spacing) * self.max_input_length

    # Calculate "X" Button Dimensions
    x_text_size = measure_text(self.x_button_text, self.font_size)
    self.x_button_width = int(x_text_size.x * 1.2)
    self.x_button_height = int(x_text_size.y * 1.2)

    # Define Keyboard Layout and Dimensions
    self.keyboard_layout = ["1234567890", "abcdef<"]
    self.keyboard_button_height = 200
    self.keyboard_spacing = 0
    self.keyboard_button_width_row1 = gui_app.width / len(self.keyboard_layout[0])
    self.keyboard_button_width_row2 = gui_app.width / len(self.keyboard_layout[1])

    # Create Widget buttons
    self._create_widgets()

  def _create_widgets(self):
    """Create Widget buttons."""
    # X button
    self._x_button = TSKButton(
      labels=self.x_button_text,
      click_callback=self._on_x_click,
      font_size=self.font_size,
      width=self.x_button_width,
      height=self.x_button_height
    )

    # Install button
    self._install_button = TSKButton(
      labels=[{"text": "Install this key", "x_offset": 50, "y_offset": 15}],
      click_callback=self._on_install_click,
      font_size=self.font_size
    )

    # Create keyboard key widgets
    self._key_buttons = {}
    for row_index, row in enumerate(self.keyboard_layout):
      for key_index, key in enumerate(row):
        key_id = f"{row_index}_{key_index}"
        self._key_buttons[key_id] = TSKButton(
          labels=key,
          click_callback=lambda k=key: self._on_key_click(k),
          font_size=self.font_size,
          width=self.keyboard_button_width_row1 if row_index == 0 else self.keyboard_button_width_row2,
          height=self.keyboard_button_height
        )

  def _on_x_click(self):
    """Handle X button click."""
    self.dialog_open = False

  def _on_install_click(self):
    """Handle install button click."""
    self.key_file_manager.install_key(self.input_text)
    self.install_success = True
    self.show_install_button = False

  def _on_key_click(self, key):
    """Handle keyboard key click."""
    if key == "<":
      self.input_text = self.input_text[:-1]
    else:
      if len(self.input_text) < self.max_input_length:
        self.input_text += key
    self.show_install_button = len(self.input_text) == self.max_input_length
    self.install_success = False

  def update_key_status(self):
    """Update the key status text."""
    key = self.key_file_manager.installed_key
    self.key_status_text = f"Key installed: {key}" if key else "Key not installed"

  def draw_keyboard(self, rect: rl.Rectangle) -> None:
    """Draw the keyboard and handle key input."""
    start_x = rect.x
    start_y = rect.y

    for row_index, row in enumerate(self.keyboard_layout):
      button_width = self.keyboard_button_width_row1 if row_index == 0 else self.keyboard_button_width_row2
      for key_index, key in enumerate(row):
        button_x = start_x + key_index * (button_width + self.keyboard_spacing)
        button_y = start_y + row_index * (self.keyboard_button_height + self.keyboard_spacing)
        button_rect = rl.Rectangle(button_x, button_y, button_width, self.keyboard_button_height)

        # Render button
        key_id = f"{row_index}_{key_index}"
        self._key_buttons[key_id].render(button_rect)

        # Draw border
        rl.draw_rectangle_lines_ex(button_rect, self.keyboard_border_thickness, self.keyboard_border_color)

  def render_dialog(self):
    """Render the keyboard dialog."""
    # Calculate vertical centering
    keyboard_height = 2 * self.keyboard_button_height
    available_height = gui_app.height - keyboard_height
    total_content_height = 0

    # Key Status Label
    self.update_key_status()
    key_status_text_size = measure_text(self.key_status_text, self.key_status_font_size)
    total_content_height += key_status_text_size.y

    # Input Box
    input_box_height = self.font_size * 1.5
    total_content_height += input_box_height

    # Remaining Characters Label / Install Button / Success Label
    total_content_height += self.font_size

    vertical_offset = (available_height - total_content_height) / 2

    # Key Status Label
    key_status_text_x = (gui_app.width - key_status_text_size.x) / 2
    key_status_text_y = 20 + vertical_offset
    rl.draw_text_ex(gui_app.font(), self.key_status_text, rl.Vector2(key_status_text_x, key_status_text_y), self.key_status_font_size, 0, rl.LIGHTGRAY)

    # Input Box
    input_box_x = (gui_app.width - self.input_box_width) / 2
    input_box_y = key_status_text_y + key_status_text_size.y + 20
    rl.draw_rectangle(int(input_box_x), int(input_box_y), int(self.input_box_width), int(input_box_height), self.input_box_bg_color)
    rl.draw_rectangle_lines(int(input_box_x), int(input_box_y), int(self.input_box_width), int(input_box_height), self.input_box_border_color)

    # Draw input text with color cycling
    input_text_x = input_box_x + 5
    input_text_y = input_box_y + (input_box_height - measure_text("A", self.font_size).y) / 2
    x_offset = 0
    for i, char in enumerate(self.input_text):
      color = self.input_text_color_1 if (i // 4) % 2 == 0 else self.input_text_color_2
      char_width = measure_text(char, self.font_size).x
      rl.draw_text_ex(gui_app.font(), char, rl.Vector2(input_text_x + x_offset, input_text_y), self.font_size, 0, color)
      x_offset += char_width + self.char_spacing

    # Remaining Characters Label / Install Button / Success Label
    remaining_chars = self.max_input_length - len(self.input_text)
    remaining_text_y = input_box_y + input_box_height + 10

    if self.install_success:
      # Success Label
      success_text = "Success!"
      success_text_size = measure_text(success_text, self.font_size)
      success_text_x = (gui_app.width - success_text_size.x) / 2
      rl.draw_text_ex(gui_app.font(), success_text, rl.Vector2(success_text_x, remaining_text_y), self.font_size, 0, rl.GREEN)

    elif self.show_install_button:
      # Install Button
      install_text = "Install this key"
      install_text_size = measure_text(install_text, self.font_size)
      install_button_width = install_text_size.x + 200
      install_button_height = install_text_size.y + 50
      install_button_x = (gui_app.width - install_button_width) / 2
      install_button_rect = rl.Rectangle(install_button_x, remaining_text_y, install_button_width, install_button_height)

      # Render install button
      self._install_button.render(install_button_rect)

    else:
      # Remaining Characters Label
      remaining_text = f"{remaining_chars} characters left"
      remaining_text_size = measure_text(remaining_text, self.font_size)
      remaining_text_x = (gui_app.width - remaining_text_size.x) / 2
      rl.draw_text_ex(gui_app.font(), remaining_text, rl.Vector2(remaining_text_x, remaining_text_y), self.font_size, 0, rl.DARKGRAY)

    # "X" Button (Top Right)
    button_x = gui_app.width - self.x_button_width
    button_y = 0
    x_button_rect = rl.Rectangle(button_x, button_y, self.x_button_width, self.x_button_height)
    self._x_button.render(x_button_rect)

    # Keyboard
    keyboard_x = 0
    keyboard_y = gui_app.height - 2 * self.keyboard_button_height
    keyboard_width = gui_app.width
    keyboard_height = 2 * self.keyboard_button_height
    self.draw_keyboard(rl.Rectangle(keyboard_x, keyboard_y, keyboard_width, keyboard_height))

  @staticmethod
  def ask():
    """Display the TSK Keyboard dialog."""
    dialog = KeyboardDialog()

    # Get the current key and set it as the default text
    installed_key = dialog.key_file_manager.installed_key
    if installed_key:
      dialog.input_text = installed_key
      dialog.show_install_button = len(dialog.input_text) == dialog.max_input_length

    dialog.update_key_status()

    for _ in render_loop():
      if not dialog.dialog_open or rl.window_should_close():
        break

      dialog.render_dialog()
