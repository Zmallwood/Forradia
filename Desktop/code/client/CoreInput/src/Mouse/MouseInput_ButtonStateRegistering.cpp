/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseInput.hpp"

namespace Forradia {
void MouseInput::RegisterMouseButtonDown(Uint8 button) {
  switch (button) {
  case SDL_BUTTON_LEFT:
    m_leftMouseButton.RegisterPress();
    break;
  case SDL_BUTTON_RIGHT:
    m_rightMouseButton.RegisterPress();
    break;
  }
}

void MouseInput::RegisterMouseButtonUp(Uint8 button) {
  switch (button) {
  case SDL_BUTTON_LEFT:
    m_leftMouseButton.RegisterRelease();
    break;

  case SDL_BUTTON_RIGHT:
    m_rightMouseButton.RegisterRelease();
    break;
  }
}
}