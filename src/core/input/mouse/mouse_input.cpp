/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "mouse_input.hpp"

namespace forr {
  void mouse_input::reset() {
    m_left_mouse_button.reset();
    m_right_mouse_button.reset();
  }

  void mouse_input::register_mouse_button_down(Uint8 mouse_button) {
    switch (mouse_button) {
    case SDL_BUTTON_LEFT:
      m_left_mouse_button.register_press();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_mouse_button.register_press();
      break;
    }
  }

  void mouse_input::register_mouse_button_up(Uint8 mouse_button) {
    switch (mouse_button) {
    case SDL_BUTTON_LEFT:
      m_left_mouse_button.register_release();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_mouse_button.register_release();
      break;
    }
  }

  bool mouse_input::any_mouse_button_is_pressed_pick_result() {
    auto any_mouse_button_is_pressed_result{
        m_left_mouse_button.is_pressed_pick_result()};
    any_mouse_button_is_pressed_result |=
        m_right_mouse_button.is_pressed_pick_result();
    return any_mouse_button_is_pressed_result;
  }
}