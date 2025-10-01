/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "keyboard_input.hpp"

namespace forr {
  void keyboard_input::reset() { m_pressedKeys.clear(); }

  void keyboard_input::register_key_press(SDL_Keycode key) {
    m_pressedKeys.insert(key);
  }

  void keyboard_input::register_key_release(SDL_Keycode key) {
    m_pressedKeys.erase(key);
  }

  bool keyboard_input::key_is_pressed(SDL_Keycode key) const {
    return m_pressedKeys.contains(key);
  }

  bool keyboard_input::key_is_pressed_pick_result(SDL_Keycode key) {
    auto keyIsPressedResult{m_pressedKeys.contains(key)};
    m_pressedKeys.erase(key);
    return keyIsPressedResult;
  }

  bool keyboard_input::any_key_is_pressed_pick_result() {
    auto anyKeyIsPressedResult{m_pressedKeys.size() > 0};
    m_pressedKeys.clear();
    return anyKeyIsPressedResult;
  }
}
