/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "setupScenes.hpp"
#include "ForradiaEngine/ScenesCore.hpp"
#include "Scenes/IntroScene.hpp"
#include "Scenes/MainScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/PlayScene.hpp"
#include "Scenes/WorldGenerationScene.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto setupScenes(WorldGenerator &worldGenerator) -> void
    {
        SceneManager::instance().addScene("IntroScene", std::make_shared<IntroScene>());
        SceneManager::instance().addScene("MainMenuScene", std::make_shared<MainMenuScene>());
        SceneManager::instance().addScene("PlayScene", std::make_shared<PlayScene>());
        SceneManager::instance().addScene("WorldGenerationScene", std::make_shared<WorldGenerationScene>(worldGenerator));
        SceneManager::instance().addScene("MainScene", std::make_shared<MainScene>());

        SceneManager::instance().goToScene("IntroScene");
    }
}
