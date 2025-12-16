/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Cursor.hpp"
#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
void Cursor::Initialize() {
  this->DisableSystemCursor();
}

void Cursor::DisableSystemCursor() const {
  SDL_ShowCursor(SDL_DISABLE);
}

void Cursor::ResetStyleToNormal() {
  m_cursorStyle = CursorStyles::Normal;
}

void Cursor::Render() const {
  auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

  auto width{k_cursorSize};
  auto height{ConvertWidthToHeight(k_cursorSize, _<SDLDevice>().GetWindow())};

  String cursorImage;

  switch (m_cursorStyle) {
  case CursorStyles::Normal:
    cursorImage = "CursorNormal";
    break;

  case CursorStyles::HoveringClickableGUI:
    cursorImage = "CursorHoveringClickableGUI";
    break;
  }

  _<Image2DRenderer>().DrawImageByName(k_renderID, cursorImage, mousePosition.x - width / 2,
                                       mousePosition.y - height / 2, width, height, true);
}
}