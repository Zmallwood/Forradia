/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "mouse_button.hpp"

namespace forr {
  void mouse_button::reset() {
    m_isPressed = false;
    m_hasBeenFired = false;
    m_hasBeenReleased = false;
  }

  void mouse_button::register_press() {
    m_isPressed = true;
    m_hasBeenFired = true;
  }

  void mouse_button::register_release() {
    m_isPressed = false;
    m_hasBeenReleased = true;
  }

  bool mouse_button::is_pressed_pick_result() {
    auto isPressedResult{m_isPressed};
    m_isPressed = false;
    return isPressedResult;
  }

  bool mouse_button::get_has_been_fired_pick_result() {
    auto hasBeenFiredResult{m_hasBeenFired};
    m_hasBeenFired = false;
    return hasBeenFiredResult;
  }

  bool mouse_button::get_has_been_fired_dont_pick_result() {
    return m_hasBeenFired;
  }

  bool mouse_button::get_has_been_released_pick_result() {
    auto hasBeenReleasedResult{m_hasBeenReleased};
    m_hasBeenReleased = false;
    return hasBeenReleasedResult;
  }

  bool mouse_button::get_has_been_released_dont_pick_result() {
    return m_hasBeenReleased;
  }
}