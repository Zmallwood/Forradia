/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SetupScenes.hpp"
#include "Intro/IntroScene.hpp"
#include "MainMenu/MainMenuScene.hpp"
#include "Main/MainScene.hpp"
#include "Play/PlayScene.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "WorldGeneration/WorldGenerationScene.hpp"

namespace Forradia::Theme0
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
