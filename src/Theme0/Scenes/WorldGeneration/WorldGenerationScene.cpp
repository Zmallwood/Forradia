/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "WorldGenerationScene.hpp"
#include "Theme0/Theme0Mechanics/WorldGeneration/GenerateNewWorld.hpp"
#include "Core/ScenesCore/SceneManager.hpp"

namespace Forradia
{
    void WorldGenerationScene::OnEnterDerived()
    {
        GenerateNewWorld();

        _<SceneManager>().GoToScene("MainScene");
    }
}
