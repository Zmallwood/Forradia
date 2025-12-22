/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SetupScenes.hpp"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "MainScene.hpp"
#include "PlayScene.hpp"
#include "SceneManager.hpp"
#include "WorldGenerationScene.hpp"

namespace Forradia::Theme0 {
    auto SetupScenes() -> void {
        SceneManager::Instance().AddScene("IntroScene", IntroScene::Instance());
        SceneManager::Instance().AddScene("MainMenuScene", MainMenuScene::Instance());
        SceneManager::Instance().AddScene("PlayScene", PlayScene::Instance());
        SceneManager::Instance().AddScene("WorldGenerationScene", WorldGenerationScene::Instance());
        SceneManager::Instance().AddScene("MainScene", MainScene::Instance());

        SceneManager::Instance().GoToScene("IntroScene");
    }
}
