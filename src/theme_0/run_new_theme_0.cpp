/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "run_new_theme_0.hpp"
#include "core/core.hpp"
#include "theme_0/scenes/intro/intro_scene.hpp"
#include "theme_0/scenes/main/main_scene.hpp"
#include "theme_0/scenes/main_menu/main_menu_scene.hpp"
#include "theme_0/scenes/world_generation/world_generation_scene.hpp"

namespace forr {
  void run_new_theme_0() {
    get_ston<scene_manager>().add_scene("IntroScene", get_ston<intro_scene>());
    get_ston<scene_manager>().add_scene("MainMenuScene",
                                        get_ston<main_menu_scene>());
    get_ston<scene_manager>().add_scene("WorldGenerationScene",
                                        get_ston<world_generation_scene>());
    get_ston<scene_manager>().add_scene("MainScene", get_ston<main_scene>());
    get_ston<scene_manager>().go_to_scene("IntroScene");
    get_ston<game>().start();
  }
}
