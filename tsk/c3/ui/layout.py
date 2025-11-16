# tsk/c3/ui/layout.py
import pyray as rl

class Theme:
  """Defines the visual theme and constants for the TSK Manager."""

  # --- Colors ---
  key_text_color = rl.Color(255, 255, 255, 255)
  key_bg_color = rl.Color(40, 40, 40, 255)
  button_color = rl.Color(50, 50, 50, 255)
  title_bg_color = rl.Color(60, 60, 60, 255)
  nav_text_color = rl.Color(255, 255, 255, 255)

  # --- Font Sizes ---
  title_font_size = 70
  nav_button_font_size = 60
  key_status_font_size = 50

  # --- Text ---
  nav_button_text_left = "< Tools\n< Menu"
  nav_button_text_right = "Reboot >\n   Menu >"
  nav_button_text_to_tools = "< Tools\n< Menu"

  # --- Layout ---
  title_prefix_x_offset_percent = 0.2
  title_x_offset = 180
  brighten_amount = 0.6
  status_update_interval = 1  # seconds

  # --- Menu Identifiers ---
  menu_tools = 1
  menu_reboot = 2

  menu_names = {
    menu_tools: "Tools Menu",
    menu_reboot: "Reboot Menu",
  }

  @staticmethod
  def brighten_color(color: rl.Color, amount: float) -> rl.Color:
    """Brightens a color by a given amount (0.0 to 1.0)."""
    r = int(min(color.r + (255 - color.r) * amount, 255))
    g = int(min(color.g + (255 - color.g) * amount, 255))
    b = int(min(color.b + (255 - color.b) * amount, 255))
    return rl.Color(r, g, b, color.a)


class Layout:
  """Provides layout calculation functions."""

  @staticmethod
  def calculate_button_dimensions(rect_height: int, header_height: int) -> int:
    """Calculates button height based on available screen space and desired spacing."""
    available_height = rect_height - header_height
    guide_button_height = 200
    num_spacers = 3  # Top, between buttons, and below guide button
    remaining_height = available_height - guide_button_height - (num_spacers * 80)
    button_height = remaining_height
    return int(button_height)

  @staticmethod
  def calculate_button_positions(rect: rl.Rectangle, num_buttons: int) -> tuple:
    """
    Calculates the starting positions for a row of buttons.

    Args:
      rect: The rectangle area for the menu (already positioned after header)
      num_buttons: Number of buttons to position horizontally

    Returns:
      Tuple of (start_x, start_y) for the first button position
    """
    total_width = (num_buttons * 600) + ((num_buttons - 1) * 80)
    start_x = (rect.width - total_width) / 2 + rect.x
    start_y = rect.y + 80  # Top spacer
    return start_x, start_y
