/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "mouse_button.hpp"

namespace forr {
  class mouse_input {
  public:
    void reset();

    void register_mouse_button_down(Uint8 mouseButton);

    void register_mouse_button_up(Uint8 mouseButton);

    bool any_mouse_button_is_pressed_pick_result();

    auto &get_left_mouse_button_ref() { return m_leftMouseButton; }

    auto &get_right_mouse_button_ref() { return m_leftMouseButton; }

  private:
    mouse_button m_leftMouseButton;
    mouse_button m_rightMouseButton;
  };
}