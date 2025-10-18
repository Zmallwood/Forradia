/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
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
class mouse_inp {
 public:
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

  class left_mouse_btn :public mouse_btn {
   public:
    using mouse_btn::reset;

    using mouse_btn::reg_press;

    using mouse_btn::reg_release;

    using mouse_btn::pressed_pick_res;

    using mouse_btn::been_fired_pick_res;

    using mouse_btn::been_fired_no_pick_res;

    using mouse_btn::been_released_pick_res;

    using mouse_btn::been_released_no_pick_res;
  };

  class right_mouse_btn :public mouse_btn {
   public:
    using mouse_btn::reset;

    using mouse_btn::reg_press;

    using mouse_btn::reg_release;

    using mouse_btn::pressed_pick_res;

    using mouse_btn::been_fired_pick_res;

    using mouse_btn::been_fired_no_pick_res;

    using mouse_btn::been_released_pick_res;

    using mouse_btn::been_released_no_pick_res;
  };

  void reset();

  void reg_mouse_btn_down(Uint8 btn);

  void reg_mouse_btn_up(Uint8 btn);

  bool any_mouse_btn_pressed_pick_res();
};
_NS_END_