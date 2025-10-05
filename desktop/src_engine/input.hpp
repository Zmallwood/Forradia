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
  class kb_inp {
   public:
    void reset();

    void reg_key_press(SDL_Keycode key);

    void reg_key_release(SDL_Keycode key);

    bool key_pressed(SDL_Keycode key) const;

    bool key_pressed_pick_res(SDL_Keycode key);

    bool any_key_pressed_pick_res();

   private:
    std::set<SDL_Keycode> pressed_;
  };

  ////////////////////
  // Mouse
  ////////////////////
  class mouse_btn {
   public:
    void reset();

    void reg_press();

    void reg_release();

    bool pressed_pick_res();

    bool been_fired_pick_res();

    bool been_fired_no_pick_res();

    bool been_released_pick_res();

    bool been_released_no_pick_res();

   private:
    bool pressed_{false};
    bool been_fired_{false};
    bool been_released_{false};
  };

  class mouse_inp {
   public:
    void reset();

    void reg_mouse_btn_down(Uint8 btn);

    void reg_mouse_btn_up(Uint8 btn);

    bool any_mouse_btn_pressed_pick_res();

    auto &left_btn_ref() { return left_btn_; }

    auto &right_btn_ref() { return right_btn_; }

   private:
    mouse_btn left_btn_;
    mouse_btn right_btn_;
  };
}