/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SetupScenes.hpp"

#include "ForradiaEngine/ScenesCore.hpp"
#include "IntroScene.hpp"
#include "MainScene.hpp"
#include "MainMenuScene.hpp"
#include "PlayScene.hpp"
#include "WorldGenerationScene.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto setupScenes() -> void
    {
        SceneManager::instance().addScene("IntroScene", IntroScene::instance());
        SceneManager::instance().addScene("MainMenuScene", MainMenuScene::instance());
        SceneManager::instance().addScene("PlayScene", PlayScene::instance());
        SceneManager::instance().addScene("WorldGenerationScene", WorldGenerationScene::instance());
        SceneManager::instance().addScene("MainScene", MainScene::instance());

        SceneManager::instance().goToScene("IntroScene");
    }
}
