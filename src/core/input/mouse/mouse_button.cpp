/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "mouse_button.hpp"

namespace forr {
  void mouse_button::reset() {
    m_is_pressed = false;
    m_has_been_fired = false;
    m_has_been_released = false;
  }

  void mouse_button::register_press() {
    m_is_pressed = true;
    m_has_been_fired = true;
  }

  void mouse_button::register_release() {
    m_is_pressed = false;
    m_has_been_released = true;
  }

  bool mouse_button::is_pressed_pick_result() {
    auto is_pressed_result{m_is_pressed};
    m_is_pressed = false;
    return is_pressed_result;
  }

  bool mouse_button::get_has_been_fired_pick_result() {
    auto has_been_fired_result{m_has_been_fired};
    m_has_been_fired = false;
    return has_been_fired_result;
  }

  bool mouse_button::get_has_been_fired_dont_pick_result() {
    return m_has_been_fired;
  }

  bool mouse_button::get_has_been_released_pick_result() {
    auto has_been_released_result{m_has_been_released};
    m_has_been_released = false;
    return has_been_released_result;
  }

  bool mouse_button::get_has_been_released_dont_pick_result() {
    return m_has_been_released;
  }
}