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
    _<scene_manager>().add_scene("IntroScene", _<intro_scene>());
    _<scene_manager>().add_scene("MainMenuScene", _<main_menu_scene>());
    _<scene_manager>().add_scene("WorldGenerationScene",
                                 _<world_generation_scene>());
    _<scene_manager>().add_scene("MainScene", _<main_scene>());
    _<scene_manager>().go_to_scene("IntroScene");
    _<game>().start();
  }
}
