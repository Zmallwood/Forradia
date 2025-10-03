/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  ////////////////////
  // Keyboard
  ////////////////////
  class kb_input {
   public:
    void reset();

    void reg_key_press(SDL_Keycode key);

    void reg_key_release(SDL_Keycode key);

    bool key_pressed(SDL_Keycode key) const;

    bool key_pressed_pick_result(SDL_Keycode key);

    bool any_key_pressed_pick_result();

   private:
    std::set<SDL_Keycode> pressed_;
  };

  ////////////////////
  // Mouse
  ////////////////////
  class mouse_button {
   public:
    void reset();

    void reg_press();

    void reg_release();

    bool pressed_pick_result();

    bool get_been_fired_pick_result();

    bool get_been_fired_dont_pick_result();

    bool get_been_released_pick_result();

    bool get_been_released_dont_pick_result();

   private:
    bool pressed_{false};
    bool been_fired_{false};
    bool been_released_{false};
  };

  class mouse_input {
   public:
    void reset();

    void reg_mouse_button_down(Uint8 btn);

    void reg_mouse_button_up(Uint8 btn);

    bool any_mouse_button_pressed_pick_result();

    auto &get_left_btn_ref() { return left_btn_; }

    auto &get_right_btn_ref() { return right_btn_; }

   private:
    mouse_button left_btn_;
    mouse_button right_btn_;
  };
}