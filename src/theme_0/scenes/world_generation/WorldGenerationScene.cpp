/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "WorldGenerationScene.hpp"
#include "core/gui_core/GUITextConsole.hpp"
#include "core/scenes_core/SceneManager.hpp"
#include "theme_0/theme_0_mechanics/world_generation/GenerateNewWorld.hpp"

namespace Forradia {
  void WorldGenerationScene::OnEnterDerived() {
    GetSingleton<GUITextConsole>().Print("Generating new world...");

    GenerateNewWorld();

    GetSingleton<GUITextConsole>().Print("World generation completed.");

    GetSingleton<SceneManager>().GoToScene("MainScene");
  }
}
