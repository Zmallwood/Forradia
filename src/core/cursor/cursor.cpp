/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "cursor.hpp"
#include "core/rendering/images/image_renderer.hpp"

namespace forr {
  void cursor::Initialize() { DisableSystemCursor(); }

  void cursor::DisableSystemCursor() { SDL_ShowCursor(SDL_DISABLE); }

  void cursor::ResetStyleToDefault() { m_cursorStyle = cursor_styles::Default; }

  void cursor::Render() {
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
    GetSingleton<image_renderer>().DrawImage(
        cursorImage, mousePosition.x - width / 2, mousePosition.y - height / 2,
        width, height);
  }
}