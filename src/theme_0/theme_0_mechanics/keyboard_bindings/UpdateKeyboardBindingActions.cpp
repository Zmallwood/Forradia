/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateKeyboardBindingActions.hpp"
#include "core/input/keyboard/KeyboardInput.hpp"
#include "theme_0/theme_0_mechanics/gui/GUIInventoryWindow.hpp"
#include "theme_0/theme_0_mechanics/gui/GUIPlayerBodyWindow.hpp"
#include "theme_0/theme_0_mechanics/gui/GUISystemMenu.hpp"

namespace Forradia {
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