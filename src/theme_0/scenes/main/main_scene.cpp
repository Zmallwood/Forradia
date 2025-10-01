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
  void MainScene::InitializeDerived() { AddMainSceneGUIComponents(GetGUI()); }

  void MainScene::OnEnterDerived() {
    GetSingleton<GUITextConsole>().Print("You have entered the world.");
  }

  void MainScene::UpdateDerived() {
    UpdateCreatureMovement();
    UpdateMouseMovement();
    UpdateKeyboardMovement();
    GetSingleton<TileHovering>().Update();
    UpdateKeyboardBindingActions();
  }

  void MainScene::RenderDerived() const { GetSingleton<WorldView>().Render(); }
}
