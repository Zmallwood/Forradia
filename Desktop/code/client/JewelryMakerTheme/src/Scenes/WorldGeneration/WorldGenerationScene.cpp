/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGenerationScene.hpp"
    
    #include "Content/WorldGeneration/Main/WorldGenerator.hpp"
    #include "ForradiaEngine/GUICore/GUIChatBox.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGenerationScene::onEnterDerived() -> void
    {
        GUIChatBox::instance().print("Generating world...");

        WorldGenerator::instance().generateNewWorld();

        GUIChatBox::instance().print("World generation complete.");

        SceneManager::instance().goToScene("MainScene");
    }
}
