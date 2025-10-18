/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "input.hpp"

_NS_START_
////////////////////
// Keyboard
////////////////////
void kb_inp::reset() { pressed_.clear(); }

void kb_inp::reg_key_press(SDL_Keycode key) { pressed_.insert(key); }

void kb_inp::reg_key_release(SDL_Keycode key) { pressed_.erase(key); }

bool kb_inp::key_pressed(SDL_Keycode key) const {
  return pressed_.contains(key);
}

bool kb_inp::key_pressed_pick_res(SDL_Keycode key) {
  auto res{pressed_.contains(key)};
  pressed_.erase(key);
  return res;
}

bool kb_inp::any_key_pressed_pick_res() {
  auto res{pressed_.size() > 0};
  pressed_.clear();
  return res;
}

////////////////////
// Mouse
////////////////////
void mouse_inp::mouse_btn::reset() {
  pressed_ = false;
  been_fired_ = false;
  been_released_ = false;
}

void mouse_inp::mouse_btn::reg_press() {
  pressed_ = true;
  been_fired_ = true;
}

void mouse_inp::mouse_btn::reg_release() {
  pressed_ = false;
  been_released_ = true;
}

bool mouse_inp::mouse_btn::pressed_pick_res() {
  auto res{pressed_};
  pressed_ = false;
  return res;
}

bool mouse_inp::mouse_btn::been_fired_pick_res() {
  auto res{been_fired_};
  been_fired_ = false;
  return res;
}

bool mouse_inp::mouse_btn::been_fired_no_pick_res() { return been_fired_; }

bool mouse_inp::mouse_btn::been_released_pick_res() {
  auto res{been_released_};
  been_released_ = false;
  return res;
}

bool mouse_inp::mouse_btn::been_released_no_pick_res() {
  return been_released_;
}

void mouse_inp::reset() {
  _<left_mouse_btn>().reset();
  _<right_mouse_btn>().reset();
}

void mouse_inp::reg_mouse_btn_down(Uint8 btn) {
  switch (btn) {
  case SDL_BUTTON_LEFT:
    _<left_mouse_btn>().reg_press();
    break;
  case SDL_BUTTON_RIGHT:
    _<right_mouse_btn>().reg_press();
    break;
  }
}

void mouse_inp::reg_mouse_btn_up(Uint8 btn) {
  switch (btn) {
  case SDL_BUTTON_LEFT:
    _<left_mouse_btn>().reg_release();
    break;
  case SDL_BUTTON_RIGHT:
    _<right_mouse_btn>().reg_release();
    break;
  }
}

bool mouse_inp::any_mouse_btn_pressed_pick_res() {
  auto res{_<left_mouse_btn>().pressed_pick_res()};
  res |= _<right_mouse_btn>().pressed_pick_res();
  return res;
}
_NS_END_