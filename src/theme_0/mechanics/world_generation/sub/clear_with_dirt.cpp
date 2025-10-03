/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "clear_with_dirt.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void clear_with_dirt() {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    sz.w *= get_ston<game_properties>().k_world_scaling;
    sz.h *= get_ston<game_properties>().k_world_scaling;
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