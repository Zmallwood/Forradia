/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_kb_binding_actions.hpp"
#include "input.hpp"
#include "theme_0/func/gui/gui_inventory_window.hpp"
#include "theme_0/func/gui/gui_player_body_window.hpp"
#include "theme_0/func/gui/gui_system_menu.hpp"

namespace forr {
  void update_kb_binding_actions() {
    if (_<kb_input>().key_pressed_pick_result(SDLK_ESCAPE)) {
      _<gui_system_menu>().toggle_visibility();
    } else if (_<kb_input>().key_pressed_pick_result(SDLK_c)) {
      _<gui_player_body_window>().toggle_visibility();
    } else if (_<kb_input>().key_pressed_pick_result(SDLK_b)) {
      _<gui_inventory_window>().toggle_visibility();
    }
  }
}