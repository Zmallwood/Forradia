/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "SetupScenes.hpp"
    #include "ForradiaEngine/ScenesCore/SceneManager.hpp"
    #include "Intro/IntroScene.hpp"
    #include "Main/MainScene.hpp"
    #include "MainMenu/MainMenuScene.hpp"
    #include "Play/PlayScene.hpp"
    #include "WorldGeneration/WorldGenerationScene.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
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
