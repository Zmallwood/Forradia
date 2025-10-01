/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "cursor.hpp"
#include "core/rendering/images/image_renderer.hpp"

namespace forr {
  void cursor::initialize() { disable_system_cursor(); }

  void cursor::disable_system_cursor() { SDL_ShowCursor(SDL_DISABLE); }

  void cursor::reset_style_to_default() {
    m_cursorStyle = cursor_styles::Default;
  }

  void cursor::render() {
    auto mousePosition{GetNormalizedMousePosition()};
    auto width{k_cursorSize};
    auto height{ConvertWidthToHeight(k_cursorSize)};
    str cursorImage;
    switch (m_cursorStyle) {
    case cursor_styles::Default:
      cursorImage = "CursorDefault";
      break;
    case cursor_styles::HoveringClickableGUI:
      cursorImage = "CursorHoveringClickableGUI";
      break;
    }
    GetSingleton<image_renderer>().draw_image(
        cursorImage, mousePosition.x - width / 2, mousePosition.y - height / 2,
        width, height);
  }
}