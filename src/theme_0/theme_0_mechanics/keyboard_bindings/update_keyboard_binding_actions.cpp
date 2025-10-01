/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_keyboard_binding_actions.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_inventory_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_body_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_system_menu.hpp"

namespace forr {
  void UpdateKeyboardBindingActions() {
    if (GetSingleton<keyboard_input>().KeyIsPressedPickResult(SDLK_ESCAPE)) {
      GetSingleton<gui_system_menu>().ToggleVisibility();
    } else if (GetSingleton<keyboard_input>().KeyIsPressedPickResult(SDLK_c)) {
      GetSingleton<gui_player_body_window>().ToggleVisibility();
    } else if (GetSingleton<keyboard_input>().KeyIsPressedPickResult(SDLK_b)) {
      GetSingleton<gui_inventory_window>().ToggleVisibility();
    }
  }
}