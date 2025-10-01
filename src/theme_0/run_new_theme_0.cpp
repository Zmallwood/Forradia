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

namespace forr {
  void RunNewTheme0() {
    GetSingleton<scene_manager>().add_scene("IntroScene",
                                            GetSingleton<intro_scene>());
    GetSingleton<scene_manager>().add_scene("MainMenuScene",
                                            GetSingleton<main_menu_scene>());
    GetSingleton<scene_manager>().add_scene(
        "WorldGenerationScene", GetSingleton<world_generation_scene>());
    GetSingleton<scene_manager>().add_scene("MainScene",
                                            GetSingleton<main_scene>());
    GetSingleton<scene_manager>().go_to_scene("IntroScene");
    GetSingleton<game>().start();
  }
}
