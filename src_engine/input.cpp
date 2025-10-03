/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "input.hpp"

namespace forr {
  ////////////////////
  // Keyboard
  ////////////////////
  void kb_input::reset() { m_pressed.clear(); }

  void kb_input::reg_key_press(SDL_Keycode key) { m_pressed.insert(key); }

  void kb_input::reg_key_release(SDL_Keycode key) { m_pressed.erase(key); }

  bool kb_input::key_pressed(SDL_Keycode key) const {
    return m_pressed.contains(key);
  }

  bool kb_input::key_pressed_pick_result(SDL_Keycode key) {
    auto res{m_pressed.contains(key)};
    m_pressed.erase(key);
    return res;
  }

  bool kb_input::any_key_pressed_pick_result() {
    auto res{m_pressed.size() > 0};
    m_pressed.clear();
    return res;
  }

  ////////////////////
  // Mouse
  ////////////////////
  void mouse_button::reset() {
    m_pressed = false;
    m_been_fired = false;
    m_been_released = false;
  }

  void mouse_button::reg_press() {
    m_pressed = true;
    m_been_fired = true;
  }

  void mouse_button::reg_release() {
    m_pressed = false;
    m_been_released = true;
  }

  bool mouse_button::pressed_pick_result() {
    auto res{m_pressed};
    m_pressed = false;
    return res;
  }

  bool mouse_button::get_been_fired_pick_result() {
    auto res{m_been_fired};
    m_been_fired = false;
    return res;
  }

  bool mouse_button::get_been_fired_dont_pick_result() { return m_been_fired; }

  bool mouse_button::get_been_released_pick_result() {
    auto res{m_been_released};
    m_been_released = false;
    return res;
  }

  bool mouse_button::get_been_released_dont_pick_result() {
    return m_been_released;
  }

  void mouse_input::reset() {
    m_left_btn.reset();
    m_right_btn.reset();
  }

  void mouse_input::reg_mouse_button_down(Uint8 btn) {
    switch (btn) {
    case SDL_BUTTON_LEFT:
      m_left_btn.reg_press();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_btn.reg_press();
      break;
    }
  }

  void mouse_input::reg_mouse_button_up(Uint8 btn) {
    switch (btn) {
    case SDL_BUTTON_LEFT:
      m_left_btn.reg_release();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_btn.reg_release();
      break;
    }
  }

  bool mouse_input::any_mouse_button_pressed_pick_result() {
    auto res{m_left_btn.pressed_pick_result()};
    res |= m_right_btn.pressed_pick_result();
    return res;
  }
}