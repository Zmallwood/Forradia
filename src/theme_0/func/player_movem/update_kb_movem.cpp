/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_kb_movem.hpp"
#include "input.hpp"
#include "theme_0/func/core_objs/player.hpp"

namespace forr {
  void update_kb_movem() {
    auto up_press{_<kb_input>().key_pressed(SDLK_UP)};
    auto right_press{_<kb_input>().key_pressed(SDLK_RIGHT)};
    auto down_press{_<kb_input>().key_pressed(SDLK_DOWN)};
    auto left_press{_<kb_input>().key_pressed(SDLK_LEFT)};
    if (up_press || right_press || down_press || left_press) {
      _<player>().set_dest({-1, -1});
    }
    auto now{get_ticks()};
    if (now >= _<player>().get_ticks_last_move() +
                   inv_movem_spd(_<player>().get_movem_spd()) &&
        (up_press || right_press || down_press || left_press)) {
      if (up_press) {
        _<player>().move_n();
      }
      if (right_press) {
        _<player>().move_e();
      }
      if (down_press) {
        _<player>().move_s();
      }
      if (left_press) {
        _<player>().move_w();
      }
      _<player>().set_ticks_last_move(now);
    }
  }
}