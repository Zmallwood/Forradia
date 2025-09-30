/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MainScene.hpp"
#include "core/gui_core/GUITextConsole.hpp"
#include "sub/AddMainSceneGUIComponents.hpp"
#include "theme_0/theme_0_mechanics/creature_movement/UpdateCreatureMovement.hpp"
#include "theme_0/theme_0_mechanics/keyboard_bindings/UpdateKeyboardBindingActions.hpp"
#include "theme_0/theme_0_mechanics/player_movement/UpdateKeyboardMovement.hpp"
#include "theme_0/theme_0_mechanics/player_movement/UpdateMouseMovement.hpp"
#include "theme_0/theme_0_mechanics/world_interaction/TileHovering.hpp"
#include "theme_0/theme_0_mechanics/world_view/WorldView.hpp"

namespace Forradia {
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
