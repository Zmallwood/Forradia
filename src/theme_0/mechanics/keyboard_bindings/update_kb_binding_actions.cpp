/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_kb_binding_actions.hpp"
#include "core/input.hpp"
#include "theme_0/mechanics/gui/gui_inventory_window.hpp"
#include "theme_0/mechanics/gui/gui_player_body_window.hpp"
#include "theme_0/mechanics/gui/gui_system_menu.hpp"

namespace forr {
  void update_kb_binding_actions() {
    if (get_ston<keyboard_input>().key_pressed_pick_result(SDLK_ESCAPE)) {
      get_ston<gui_system_menu>().toggle_visibility();
    } else if (get_ston<keyboard_input>().key_pressed_pick_result(SDLK_c)) {
      get_ston<gui_player_body_window>().toggle_visibility();
    } else if (get_ston<keyboard_input>().key_pressed_pick_result(SDLK_b)) {
      get_ston<gui_inventory_window>().toggle_visibility();
    }
  }
}