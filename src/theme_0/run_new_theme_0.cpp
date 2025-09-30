/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "run_new_theme_0.hpp"
#include "core/game.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "theme_0/scenes/intro/intro_scene.hpp"
#include "theme_0/scenes/main/main_scene.hpp"
#include "theme_0/scenes/main_menu/main_menu_scene.hpp"
#include "theme_0/scenes/world_generation/world_generation_scene.hpp"

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
