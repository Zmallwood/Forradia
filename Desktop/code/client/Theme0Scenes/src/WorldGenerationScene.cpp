/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerationScene.hpp"
#include "GUIChatBox.hpp"
#include "SceneManager.hpp"
#include "WorldGenerator.hpp"

namespace Forradia::Theme0 {
    auto WorldGenerationScene::OnEnterDerived() -> void {
        Singleton<GUIChatBox>().Print("Generating world...");
        Singleton<WorldGenerator>().GenerateNewWorld();
        Singleton<GUIChatBox>().Print("World generation complete.");
        Singleton<SceneManager>().GoToScene("MainScene");
    }
}
