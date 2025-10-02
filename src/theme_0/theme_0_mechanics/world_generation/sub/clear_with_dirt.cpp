/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "clear_with_dirt.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void clear_with_dirt() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    size.w *= get_singleton<game_properties>().k_worldScalingFactor;
    size.h *= get_singleton<game_properties>().k_worldScalingFactor;
    for (auto y = 0; y < size.h; y++) {
      for (auto x = 0; x < size.w; x++) {
        auto tile{worldArea->get_tile(x, y)};
        if (tile) {
          tile->set_ground("GroundDirt");
        }
      }
    }
  }
}