/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "keyboard_input.hpp"

namespace forr {
  void keyboard_input::reset() { m_pressed_keys.clear(); }

  void keyboard_input::register_key_press(SDL_Keycode key) {
    m_pressed_keys.insert(key);
  }

  void keyboard_input::register_key_release(SDL_Keycode key) {
    m_pressed_keys.erase(key);
  }

  bool keyboard_input::key_is_pressed(SDL_Keycode key) const {
    return m_pressed_keys.contains(key);
  }

  bool keyboard_input::key_is_pressed_pick_result(SDL_Keycode key) {
    auto key_is_pressed_result{m_pressed_keys.contains(key)};
    m_pressed_keys.erase(key);
    return key_is_pressed_result;
  }

  bool keyboard_input::any_key_is_pressed_pick_result() {
    auto any_key_is_pressed_result{m_pressed_keys.size() > 0};
    m_pressed_keys.clear();
    return any_key_is_pressed_result;
  }
}
