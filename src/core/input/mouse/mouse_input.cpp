/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "mouse_input.hpp"

namespace forr {
  void mouse_input::Reset() {
    m_leftMouseButton.Reset();
    m_rightMouseButton.Reset();
  }

  void mouse_input::RegisterMouseButtonDown(Uint8 mouseButton) {
    switch (mouseButton) {
    case SDL_BUTTON_LEFT:
      m_leftMouseButton.RegisterPress();
      break;
    case SDL_BUTTON_RIGHT:
      m_rightMouseButton.RegisterPress();
      break;
    }
  }

  void mouse_input::RegisterMouseButtonUp(Uint8 mouseButton) {
    switch (mouseButton) {
    case SDL_BUTTON_LEFT:
      m_leftMouseButton.RegisterRelease();
      break;
    case SDL_BUTTON_RIGHT:
      m_rightMouseButton.RegisterRelease();
      break;
    }
  }

  bool mouse_input::AnyMouseButtonIsPressedPickResult() {
    auto anyMouseButtonIsPressedResult{m_leftMouseButton.IsPressedPickResult()};
    anyMouseButtonIsPressedResult |= m_rightMouseButton.IsPressedPickResult();
    return anyMouseButtonIsPressedResult;
  }
}