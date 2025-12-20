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
        _<GUIChatBox>().Print("Generating world...");
        _<WorldGenerator>().GenerateNewWorld();
        _<GUIChatBox>().Print("World generation complete.");
        _<SceneManager>().GoToScene("MainScene");
    }
}
