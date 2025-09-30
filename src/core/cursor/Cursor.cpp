/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Cursor.hpp"
#include "core/rendering/images/ImageRenderer.hpp"

namespace Forradia {
  void Cursor::Initialize() { DisableSystemCursor(); }

  void Cursor::DisableSystemCursor() { SDL_ShowCursor(SDL_DISABLE); }

  void Cursor::ResetStyleToDefault() { m_cursorStyle = CursorStyles::Default; }

  void Cursor::Render() {
    auto mousePosition{GetNormalizedMousePosition()};

    auto width{k_cursorSize};
    auto height{ConvertWidthToHeight(k_cursorSize)};

    String cursorImage;

    switch (m_cursorStyle) {
    case CursorStyles::Default:
      cursorImage = "CursorDefault";
      break;
    case CursorStyles::HoveringClickableGUI:
      cursorImage = "CursorHoveringClickableGUI";
      break;
    }

    GetSingleton<ImageRenderer>().DrawImage(cursorImage, mousePosition.x - width / 2,
                                 mousePosition.y - height / 2, width, height);
  }
}