/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "keyboard_input.hpp"

namespace forr {
  void KeyboardInput::Reset() { m_pressedKeys.clear(); }

  void KeyboardInput::RegisterKeyPress(SDL_Keycode key) {
    m_pressedKeys.insert(key);
  }

  void KeyboardInput::RegisterKeyRelease(SDL_Keycode key) {
    m_pressedKeys.erase(key);
  }

  bool KeyboardInput::KeyIsPressed(SDL_Keycode key) const {
    return m_pressedKeys.contains(key);
  }

  bool KeyboardInput::KeyIsPressedPickResult(SDL_Keycode key) {
    auto keyIsPressedResult{m_pressedKeys.contains(key)};
    m_pressedKeys.erase(key);
    return keyIsPressedResult;
  }

  bool KeyboardInput::AnyKeyIsPressedPickResult() {
    auto anyKeyIsPressedResult{m_pressedKeys.size() > 0};
    m_pressedKeys.clear();
    return anyKeyIsPressedResult;
  }
}
