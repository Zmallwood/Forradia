/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_scene.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "sub/add_main_scene_gui_components.hpp"
#include "theme_0/theme_0_mechanics/creature_movement/update_creature_movement.hpp"
#include "theme_0/theme_0_mechanics/keyboard_bindings/update_keyboard_binding_actions.hpp"
#include "theme_0/theme_0_mechanics/player_movement/update_keyboard_movement.hpp"
#include "theme_0/theme_0_mechanics/player_movement/update_mouse_movement.hpp"
#include "theme_0/theme_0_mechanics/world_interaction/tile_hovering.hpp"
#include "theme_0/theme_0_mechanics/world_view/world_view.hpp"

namespace forr {
  void main_scene::InitializeDerived() { AddMainSceneGUIComponents(GetGUI()); }

  void main_scene::OnEnterDerived() {
    GetSingleton<gui_text_console>().Print("You have entered the world.");
  }

  void main_scene::UpdateDerived() {
    UpdateCreatureMovement();
    UpdateMouseMovement();
    UpdateKeyboardMovement();
    GetSingleton<tile_hovering>().Update();
    UpdateKeyboardBindingActions();
  }

  void main_scene::RenderDerived() const {
    GetSingleton<world_view>().Render();
  }
}
