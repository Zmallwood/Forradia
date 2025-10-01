/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "keyboard_input.hpp"

namespace forr {
  void keyboard_input::Reset() { m_pressedKeys.clear(); }

  void keyboard_input::RegisterKeyPress(SDL_Keycode key) {
    m_pressedKeys.insert(key);
  }

  void keyboard_input::RegisterKeyRelease(SDL_Keycode key) {
    m_pressedKeys.erase(key);
  }

  bool keyboard_input::KeyIsPressed(SDL_Keycode key) const {
    return m_pressedKeys.contains(key);
  }

  bool keyboard_input::KeyIsPressedPickResult(SDL_Keycode key) {
    auto keyIsPressedResult{m_pressedKeys.contains(key)};
    m_pressedKeys.erase(key);
    return keyIsPressedResult;
  }

  bool keyboard_input::AnyKeyIsPressedPickResult() {
    auto anyKeyIsPressedResult{m_pressedKeys.size() > 0};
    m_pressedKeys.clear();
    return anyKeyIsPressedResult;
  }
}
