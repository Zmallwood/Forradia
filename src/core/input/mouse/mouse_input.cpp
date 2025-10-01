/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "mouse_input.hpp"

namespace forr {
  void mouse_input::reset() {
    m_leftMouseButton.reset();
    m_rightMouseButton.reset();
  }

  void mouse_input::register_mouse_button_down(Uint8 mouseButton) {
    switch (mouseButton) {
    case SDL_BUTTON_LEFT:
      m_leftMouseButton.register_press();
      break;
    case SDL_BUTTON_RIGHT:
      m_rightMouseButton.register_press();
      break;
    }
  }

  void mouse_input::register_mouse_button_up(Uint8 mouseButton) {
    switch (mouseButton) {
    case SDL_BUTTON_LEFT:
      m_leftMouseButton.register_release();
      break;
    case SDL_BUTTON_RIGHT:
      m_rightMouseButton.register_release();
      break;
    }
  }

  bool mouse_input::any_mouse_button_is_pressed_pick_result() {
    auto anyMouseButtonIsPressedResult{
        m_leftMouseButton.is_pressed_pick_result()};
    anyMouseButtonIsPressedResult |=
        m_rightMouseButton.is_pressed_pick_result();
    return anyMouseButtonIsPressedResult;
  }
}