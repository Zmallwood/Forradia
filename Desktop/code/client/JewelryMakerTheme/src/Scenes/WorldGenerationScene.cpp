/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerationScene.hpp"
#include "WorldGeneration/WorldGenerator.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGenerationScene::onEnterDerived() -> void
    {
        GUIChatBox::instance().print("Generating world...");

        m_worldGenerator.generateNewWorld();

        GUIChatBox::instance().print("World generation complete.");

        SceneManager::instance().goToScene("MainScene");
    }
}
