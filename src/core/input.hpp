/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  ////////////////////
  // Keyboard
  ////////////////////
  class keyboard_input {
   public:
    void reset();

    void register_key_press(SDL_Keycode key);

    void register_key_release(SDL_Keycode key);

    bool key_is_pressed(SDL_Keycode key) const;

    bool key_is_pressed_pick_result(SDL_Keycode key);

    bool any_key_is_pressed_pick_result();

   private:
    std::set<SDL_Keycode> m_pressed;
  };

  ////////////////////
  // Mouse
  ////////////////////
  class mouse_button {
   public:
    void reset();

    void register_press();

    void register_release();

    bool is_pressed_pick_result();

    bool get_has_been_fired_pick_result();

    bool get_has_been_fired_dont_pick_result();

    bool get_has_been_released_pick_result();

    bool get_has_been_released_dont_pick_result();

   private:
    bool m_pressed{false};
    bool m_been_fired{false};
    bool m_been_released{false};
  };

  class mouse_input {
   public:
    void reset();

    void register_mouse_button_down(Uint8 btn);

    void register_mouse_button_up(Uint8 btn);

    bool any_mouse_button_is_pressed_pick_result();

    auto &get_left_mouse_button_ref() { return m_left_btn; }

    auto &get_right_mouse_button_ref() { return m_right_btn; }

   private:
    mouse_button m_left_btn;
    mouse_button m_right_btn;
  };
}