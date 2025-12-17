/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Cursor.hpp"
#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto Cursor::Initialize() -> void {
  this->DisableSystemCursor();
}

auto Cursor::DisableSystemCursor() const -> void {
  SDL_ShowCursor(SDL_DISABLE);
}

auto Cursor::ResetStyleToNormal() -> void {
  m_cursorStyle = CursorStyles::Normal;
}

auto Cursor::Render() const -> void {
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
  case CursorStyles::HoveringCreature:
    // TODO: Add cursor image for hovering over a creature.
    cursorImage = "CursorNormal";
    break;
  }

  _<Image2DRenderer>().DrawImageByName(k_renderID, cursorImage, mousePosition.x - width / 2,
                                       mousePosition.y - height / 2, width, height, true);
}
}
