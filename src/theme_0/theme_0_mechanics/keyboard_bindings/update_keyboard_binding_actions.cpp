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
    if (GetSingleton<KeyboardInput>().KeyIsPressedPickResult(SDLK_ESCAPE)) {
      GetSingleton<GUISystemMenu>().ToggleVisibility();
    } else if (GetSingleton<KeyboardInput>().KeyIsPressedPickResult(SDLK_c)) {
      GetSingleton<GUIPlayerBodyWindow>().ToggleVisibility();
    } else if (GetSingleton<KeyboardInput>().KeyIsPressedPickResult(SDLK_b)) {
      GetSingleton<GUIInventoryWindow>().ToggleVisibility();
    }
  }
}