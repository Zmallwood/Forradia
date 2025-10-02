/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "input.hpp"

namespace forr {
  ////////////////////
  // Keyboard
  ////////////////////
  void keyboard_input::reset() { m_pressed_keys.clear(); }

  void keyboard_input::register_key_press(SDL_Keycode key) {
    m_pressed_keys.insert(key);
  }

  void keyboard_input::register_key_release(SDL_Keycode key) {
    m_pressed_keys.erase(key);
  }

  bool keyboard_input::key_is_pressed(SDL_Keycode key) const {
    return m_pressed_keys.contains(key);
  }

  bool keyboard_input::key_is_pressed_pick_result(SDL_Keycode key) {
    auto key_is_pressed_result{m_pressed_keys.contains(key)};
    m_pressed_keys.erase(key);
    return key_is_pressed_result;
  }

  bool keyboard_input::any_key_is_pressed_pick_result() {
    auto any_key_is_pressed_result{m_pressed_keys.size() > 0};
    m_pressed_keys.clear();
    return any_key_is_pressed_result;
  }

  ////////////////////
  // Mouse
  ////////////////////
  void mouse_button::reset() {
    m_is_pressed = false;
    m_has_been_fired = false;
    m_has_been_released = false;
  }

  void mouse_button::register_press() {
    m_is_pressed = true;
    m_has_been_fired = true;
  }

  void mouse_button::register_release() {
    m_is_pressed = false;
    m_has_been_released = true;
  }

  bool mouse_button::is_pressed_pick_result() {
    auto is_pressed_result{m_is_pressed};
    m_is_pressed = false;
    return is_pressed_result;
  }

  bool mouse_button::get_has_been_fired_pick_result() {
    auto has_been_fired_result{m_has_been_fired};
    m_has_been_fired = false;
    return has_been_fired_result;
  }

  bool mouse_button::get_has_been_fired_dont_pick_result() {
    return m_has_been_fired;
  }

  bool mouse_button::get_has_been_released_pick_result() {
    auto has_been_released_result{m_has_been_released};
    m_has_been_released = false;
    return has_been_released_result;
  }

  bool mouse_button::get_has_been_released_dont_pick_result() {
    return m_has_been_released;
  }

  void mouse_input::reset() {
    m_left_mouse_button.reset();
    m_right_mouse_button.reset();
  }

  void mouse_input::register_mouse_button_down(Uint8 mouse_button) {
    switch (mouse_button) {
    case SDL_BUTTON_LEFT:
      m_left_mouse_button.register_press();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_mouse_button.register_press();
      break;
    }
  }

  void mouse_input::register_mouse_button_up(Uint8 mouse_button) {
    switch (mouse_button) {
    case SDL_BUTTON_LEFT:
      m_left_mouse_button.register_release();
      break;
    case SDL_BUTTON_RIGHT:
      m_right_mouse_button.register_release();
      break;
    }
  }

  bool mouse_input::any_mouse_button_is_pressed_pick_result() {
    auto any_mouse_button_is_pressed_result{
        m_left_mouse_button.is_pressed_pick_result()};
    any_mouse_button_is_pressed_result |=
        m_right_mouse_button.is_pressed_pick_result();
    return any_mouse_button_is_pressed_result;
  }
}