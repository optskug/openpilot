#include "system/ui/raylib/util.h"
#include <cstdlib>
#include <string>

namespace {
  // Font and color settings
  const int FONT_SIZE = 100;
  const float FONT_SPACING = 1.0f;
  const Color COLOR_GRAY = RAYLIB_GRAY;
  const Color COLOR_WHITE = RAYLIB_RAYWHITE;
  const Color COLOR_BLACK = RAYLIB_BLACK;

  // Button dimensions and spacing
  const int BTN_HEIGHT = 300;
  const int BTN_WIDTH = 600;
  const int BTN_PADDING = 40;
  const int EXIT_BTN_PADDING = 20;
  const int EXIT_BTN_WIDTH = 180;
  const int EXIT_BTN_HEIGHT = 80;

  // File paths and label strings
  const std::string BASE_PATH = "/data/openpilot";
  const std::string FONT_PATH = BASE_PATH + "/selfdrive/assets/fonts/Inter-Regular.ttf";
  const std::string EXTRACT_SCRIPT = BASE_PATH + "/tsk/extract.sh";
  const std::string KEYBOARD_SCRIPT = BASE_PATH + "/system/ui/tsk-kbd";
  const std::string TEXT_EXTRACT = "TSK Extractor";
  const std::string TEXT_KEYBOARD = "TSK Keyboard";
  const std::string TEXT_EXIT = "Exit";
}

// Draws a colored rectangular button and centers text on it
void DrawButton(const Rectangle &rect, const std::string &text, const Font &font, const Color &bgColor) {
  DrawRectangleRec(rect, bgColor);
  Vector2 textSize = MeasureTextEx(font, text.c_str(), FONT_SIZE, FONT_SPACING);
  Vector2 textPos = {
    rect.x + (rect.width - textSize.x) / 2,
    rect.y + (rect.height - textSize.y) / 2
  };
  DrawTextEx(font, text.c_str(), textPos, FONT_SIZE, FONT_SPACING, COLOR_WHITE);
}

int main() {
  // Launch the app window at 30 fps
  initApp("TSK Manager", 30);

  // Load the main font; set texture filtering for better scaling
  Font regularFont = LoadFontEx(FONT_PATH.c_str(), FONT_SIZE * 2, 0, 0);
  SetTextureFilter(regularFont.texture, TEXTURE_FILTER_ANISOTROPIC_4X);
  if (!regularFont.baseSize) return 1;

  // Define button rectangles (positions and sizes)
  // Exit Button in upper-left corner by default
  Rectangle exitButton = {
    (float)EXIT_BTN_PADDING, (float)EXIT_BTN_PADDING,
    (float)EXIT_BTN_WIDTH,   (float)EXIT_BTN_HEIGHT
  };
  // Pre-calc a bottom-right position for the exit button
  Rectangle exitButtonBottomRight = {
    (float)GetScreenWidth()  - EXIT_BTN_WIDTH  - EXIT_BTN_PADDING,
    (float)GetScreenHeight() - EXIT_BTN_HEIGHT - EXIT_BTN_PADDING,
    (float)EXIT_BTN_WIDTH, (float)EXIT_BTN_HEIGHT
  };
  // Other buttons (centered horizontally)
  Rectangle extractButton = {
    (float)(GetScreenWidth() / 2 - BTN_WIDTH - BTN_PADDING / 2),
    (float)(GetScreenHeight() / 2 - BTN_HEIGHT / 2),
    (float)BTN_WIDTH, (float)BTN_HEIGHT
  };
  Rectangle keyboardButton = {
    (float)(GetScreenWidth() / 2 + BTN_PADDING / 2),
    (float)(GetScreenHeight() / 2 - BTN_HEIGHT / 2),
    (float)BTN_WIDTH, (float)BTN_HEIGHT
  };

  // Tracks how many times the exit button has been clicked:
  //   0 -> in upper-left
  //   1 -> moved to bottom-right
  //   2 -> exit program
  int exitClickCount = 0;

  while (!WindowShouldClose()) {
    // On each click, decide if it's the exit button or elsewhere
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mousePos = GetMousePosition();

      // Clicking the exit button
      if (CheckCollisionPointRec(mousePos, exitButton)) {
        if (++exitClickCount == 1) {
          // Move it to the bottom-right if this is the first click
          exitButton.x = exitButtonBottomRight.x;
          exitButton.y = exitButtonBottomRight.y;
        } else if (exitClickCount == 2) {
          // On second click, exit the loop (and the program)
          break;
        }
      } else {
        // If the button is already moved, reset it upon clicking elsewhere
        if (exitClickCount > 0) {
          exitButton.x = (float)EXIT_BTN_PADDING;
          exitButton.y = (float)EXIT_BTN_PADDING;
          exitClickCount = 0;
        }
      }
    }

    // Run system commands if the user clicks on these buttons
    if (CheckCollisionPointRec(GetMousePosition(), extractButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      system(EXTRACT_SCRIPT.c_str());
    }
    if (CheckCollisionPointRec(GetMousePosition(), keyboardButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      system(KEYBOARD_SCRIPT.c_str());
    }

    BeginDrawing();
      ClearBackground(COLOR_BLACK);
      // Draw the Exit button (may be top-left or bottom-right)
      DrawButton(exitButton, TEXT_EXIT, regularFont, COLOR_GRAY);
      DrawButton(extractButton, TEXT_EXTRACT, regularFont, COLOR_GRAY);
      DrawButton(keyboardButton, TEXT_KEYBOARD, regularFont, COLOR_GRAY);
    EndDrawing();
  }

  UnloadFont(regularFont);
  CloseWindow();
  return 0;
}
