/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerationScene.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/ScenesCore/SceneManager.hpp"
#include "Content/WorldGeneration/Main/WorldGenerator.hpp"

namespace Forradia::Theme0
{
    auto WorldGenerationScene::onEnterDerived() -> void
    {
        GUIChatBox::instance().print("Generating world...");

        WorldGenerator::instance().generateNewWorld();

        GUIChatBox::instance().print("World generation complete.");

        SceneManager::instance().goToScene("MainScene");
    }
}
