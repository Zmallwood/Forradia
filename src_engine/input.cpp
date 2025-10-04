/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "input.hpp"

namespace forr {
  ////////////////////
  // Keyboard
  ////////////////////
  void kb_input::reset() { pressed_.clear(); }

  void kb_input::reg_key_press(SDL_Keycode key) { pressed_.insert(key); }

  void kb_input::reg_key_release(SDL_Keycode key) { pressed_.erase(key); }

  bool kb_input::key_pressed(SDL_Keycode key) const {
    return pressed_.contains(key);
  }

  bool kb_input::key_pressed_pick_result(SDL_Keycode key) {
    auto res{pressed_.contains(key)};
    pressed_.erase(key);
    return res;
  }

  bool kb_input::any_key_pressed_pick_result() {
    auto res{pressed_.size() > 0};
    pressed_.clear();
    return res;
  }

  ////////////////////
  // Mouse
  ////////////////////
  void mouse_button::reset() {
    pressed_ = false;
    been_fired_ = false;
    been_released_ = false;
  }

  void mouse_button::reg_press() {
    pressed_ = true;
    been_fired_ = true;
  }

  void mouse_button::reg_release() {
    pressed_ = false;
    been_released_ = true;
  }

  bool mouse_button::pressed_pick_result() {
    auto res{pressed_};
    pressed_ = false;
    return res;
  }

  bool mouse_button::been_fired_pick_result() {
    auto res{been_fired_};
    been_fired_ = false;
    return res;
  }

  bool mouse_button::been_fired_dont_pick_result() { return been_fired_; }

  bool mouse_button::been_released_pick_result() {
    auto res{been_released_};
    been_released_ = false;
    return res;
  }

  bool mouse_button::been_released_dont_pick_result() { return been_released_; }

  void mouse_input::reset() {
    left_btn_.reset();
    right_btn_.reset();
  }

  void mouse_input::reg_mouse_btn_down(Uint8 btn) {
    switch (btn) {
    case SDL_BUTTON_LEFT:
      left_btn_.reg_press();
      break;
    case SDL_BUTTON_RIGHT:
      right_btn_.reg_press();
      break;
    }
  }

  void mouse_input::reg_mouse_btn_up(Uint8 btn) {
    switch (btn) {
    case SDL_BUTTON_LEFT:
      left_btn_.reg_release();
      break;
    case SDL_BUTTON_RIGHT:
      right_btn_.reg_release();
      break;
    }
  }

  bool mouse_input::any_mouse_btn_pressed_pick_result() {
    auto res{left_btn_.pressed_pick_result()};
    res |= right_btn_.pressed_pick_result();
    return res;
  }
}