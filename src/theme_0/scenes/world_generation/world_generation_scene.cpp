/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "world_generation_scene.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "theme_0/theme_0_mechanics/world_generation/generate_new_world.hpp"

namespace Forradia {
  void WorldGenerationScene::OnEnterDerived() {
    GetSingleton<GUITextConsole>().Print("Generating new world...");
    GenerateNewWorld();
    GetSingleton<GUITextConsole>().Print("World generation completed.");
    GetSingleton<SceneManager>().GoToScene("MainScene");
  }
}
