/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "RunNewTheme0.hpp"
#include "core/Game.hpp"
#include "core/scenes_core/SceneManager.hpp"
#include "theme_0/scenes/intro/IntroScene.hpp"
#include "theme_0/scenes/main/MainScene.hpp"
#include "theme_0/scenes/main_menu/MainMenuScene.hpp"
#include "theme_0/scenes/world_generation/WorldGenerationScene.hpp"

namespace Forradia {
  void RunNewTheme0() {
    GetSingleton<SceneManager>().AddScene("IntroScene",
                                          GetSingleton<IntroScene>());
    GetSingleton<SceneManager>().AddScene("MainMenuScene",
                                          GetSingleton<MainMenuScene>());
    GetSingleton<SceneManager>().AddScene("WorldGenerationScene",
                                          GetSingleton<WorldGenerationScene>());
    GetSingleton<SceneManager>().AddScene("MainScene",
                                          GetSingleton<MainScene>());

    GetSingleton<SceneManager>().GoToScene("IntroScene");

    GetSingleton<Game>().Start();
  }
}
