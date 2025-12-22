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
        GUIChatBox::Instance().Print("Generating world...");
        WorldGenerator::Instance().GenerateNewWorld();
        GUIChatBox::Instance().Print("World generation complete.");
        SceneManager::Instance().GoToScene("MainScene");
    }
}
