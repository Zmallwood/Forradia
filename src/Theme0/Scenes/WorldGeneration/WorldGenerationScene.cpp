/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "WorldGenerationScene.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Theme0/Theme0Mechanics/WorldGeneration/GenerateNewWorld.hpp"

namespace Forradia {
  void WorldGenerationScene::OnEnterDerived() {
    _<GUITextConsole>().Print("Generating new world...");

    GenerateNewWorld();

    _<GUITextConsole>().Print("World generation completed.");

    _<SceneManager>().GoToScene("MainScene");
  }
}
