/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class keyboard_input {
  public:
    void reset();

    void register_key_press(SDL_Keycode key);

    void register_key_release(SDL_Keycode key);

    bool key_is_pressed(SDL_Keycode key) const;

    bool key_is_pressed_pick_result(SDL_Keycode key);

    bool any_key_is_pressed_pick_result();

  private:
    std::set<SDL_Keycode> m_pressed_keys;
  };
}
