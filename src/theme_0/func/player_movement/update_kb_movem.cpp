/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_kb_movem.hpp"
#include "core/input.hpp"
#include "theme_0/func/core_game_objects/player.hpp"

namespace forr {
  void update_kb_movem() {
    auto up_press{get_ston<keyboard_input>().key_pressed(SDLK_UP)};
    auto right_press{get_ston<keyboard_input>().key_pressed(SDLK_RIGHT)};
    auto down_press{get_ston<keyboard_input>().key_pressed(SDLK_DOWN)};
    auto left_press{get_ston<keyboard_input>().key_pressed(SDLK_LEFT)};
    if (up_press || right_press || down_press || left_press) {
      get_ston<player>().set_dest({-1, -1});
    }
    auto now{get_ticks()};
    if (now >= get_ston<player>().get_ticks_last_move() +
                   inv_movem_spd(get_ston<player>().get_movem_spd()) &&
        (up_press || right_press || down_press || left_press)) {
      if (up_press) {
        get_ston<player>().move_n();
      }
      if (right_press) {
        get_ston<player>().move_e();
      }
      if (down_press) {
        get_ston<player>().move_s();
      }
      if (left_press) {
        get_ston<player>().move_w();
      }
      get_ston<player>().set_ticks_last_move(now);
    }
  }
}