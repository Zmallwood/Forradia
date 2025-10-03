/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "input.hpp"

namespace forr {
  ////////////////////
  // Keyboard
  ////////////////////
  void keyboard_input::reset() { m_pressed.clear(); }

  void keyboard_input::register_key_press(SDL_Keycode key) {
    m_pressed.insert(key);
  }

  void keyboard_input::register_key_release(SDL_Keycode key) {
    m_pressed.erase(key);
  }

  bool keyboard_input::key_is_pressed(SDL_Keycode key) const {
    return m_pressed.contains(key);
  }

  bool keyboard_input::key_is_pressed_pick_result(SDL_Keycode key) {
    auto res{m_pressed.contains(key)};
    m_pressed.erase(key);
    return res;
  }

  bool keyboard_input::any_key_is_pressed_pick_result() {
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

  void mouse_button::register_press() {
    m_pressed = true;
    m_been_fired = true;
  }

  void mouse_button::register_release() {
    m_pressed = false;
    m_been_released = true;
  }

  bool mouse_button::is_pressed_pick_result() {
    auto res{m_pressed};
    m_pressed = false;
    return res;
  }

  bool mouse_button::get_has_been_fired_pick_result() {
    auto res{m_been_fired};
    m_been_fired = false;
    return res;
  }

  bool mouse_button::get_has_been_fired_dont_pick_result() {
    return m_been_fired;
  }

  bool mouse_button::get_has_been_released_pick_result() {
    auto res{m_been_released};
    m_been_released = false;
    return res;
  }

  bool mouse_button::get_has_been_released_dont_pick_result() {
    return m_been_released;
  }

  void mouse_input::reset() {
    m_left_btn.reset();
    m_right_btn.reset();
  }

  void mouse_input::register_mouse_button_down(Uint8 btn) {
    switch (btn) {
    case SDL_BUTTON_LEFT:
      m_left_btn.register_press();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_btn.register_press();
      break;
    }
  }

  void mouse_input::register_mouse_button_up(Uint8 btn) {
    switch (btn) {
    case SDL_BUTTON_LEFT:
      m_left_btn.register_release();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_btn.register_release();
      break;
    }
  }

  bool mouse_input::any_mouse_button_is_pressed_pick_result() {
    auto res{m_left_btn.is_pressed_pick_result()};
    res |= m_right_btn.is_pressed_pick_result();
    return res;
  }
}