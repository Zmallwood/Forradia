/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "clear_with_dirt.hpp"
#include "theme_0/func/game_props.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void clear_with_dirt() {
    auto w_area{_<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    sz.w *= _<game_props>().k_world_scaling;
    sz.h *= _<game_props>().k_world_scaling;
    for (auto y = 0; y < sz.h; y++) {
      for (auto x = 0; x < sz.w; x++) {
        auto tl{w_area->get_tl(x, y)};
        if (tl) {
          tl->set_ground("GroundDirt");
        }
      }
    }
  }
}