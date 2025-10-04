/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "game_props.hpp"
#include "scenes.hpp"
#include "world_struct.hpp"

int main(int argc, char **argv) {
  using namespace forr;
  _<engine>().init(_<game_props>().k_game_win_title,
                   _<game_props>().k_clear_color);
  _<scene_mngr>().add_scene("IntroScene", _<intro_scene>());
  _<scene_mngr>().add_scene("MainMenuScene", _<main_menu_scene>());
  _<scene_mngr>().add_scene("WorldGenScene", _<world_gen_scene>());
  _<scene_mngr>().add_scene("MainScene", _<main_scene>());
  _<scene_mngr>().go_to_scene("IntroScene");
  _<world>().init(_<game_props>().k_w_area_sz, _<game_props>().k_world_scaling);
  _<engine>().run();
  return 0;
}
