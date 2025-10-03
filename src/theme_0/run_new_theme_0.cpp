/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "run_new_theme_0.hpp"
#include "core.hpp"
#include "scenes.hpp"

namespace forr {
  void run_new_theme_0() {
    _<scene_mngr>().add_scene("IntroScene", _<intro_scene>());
    _<scene_mngr>().add_scene("MainMenuScene", _<main_menu_scene>());
    _<scene_mngr>().add_scene("WorldGenScene", _<world_gen_scene>());
    _<scene_mngr>().add_scene("MainScene", _<main_scene>());
    _<scene_mngr>().go_to_scene("IntroScene");
    _<game>().start();
  }
}
