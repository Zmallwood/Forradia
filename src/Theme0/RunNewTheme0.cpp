/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "RunNewTheme0.hpp"
#include "Core/Game.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Theme0/Scenes/Intro/IntroScene.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Theme0/Scenes/MainMenu/MainMenuScene.hpp"
#include "Theme0/Scenes/WorldGeneration/WorldGenerationScene.hpp"

namespace Forradia {
  void RunNewTheme0() {
    _<SceneManager>().AddScene("IntroScene", _<IntroScene>());
    _<SceneManager>().AddScene("MainMenuScene", _<MainMenuScene>());
    _<SceneManager>().AddScene("WorldGenerationScene",
                               _<WorldGenerationScene>());
    _<SceneManager>().AddScene("MainScene", _<MainScene>());

    _<SceneManager>().GoToScene("IntroScene");

    _<Game>().Start();
  }
}
