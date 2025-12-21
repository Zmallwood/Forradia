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
        Singleton<SceneManager>().AddScene("IntroScene", Singleton<IntroScene>());
        Singleton<SceneManager>().AddScene("MainMenuScene", Singleton<MainMenuScene>());
        Singleton<SceneManager>().AddScene("PlayScene", Singleton<PlayScene>());
        Singleton<SceneManager>().AddScene("WorldGenerationScene",
                                           Singleton<WorldGenerationScene>());
        Singleton<SceneManager>().AddScene("MainScene", Singleton<MainScene>());

        Singleton<SceneManager>().GoToScene("IntroScene");
    }
}
