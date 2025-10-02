/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_npcs.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/npc.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_npcs() {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto size{world_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling_factor};
    auto num_npc_0s{200 * scale + random_int(15 * scale)};
    for (auto i = 0; i < num_npc_0s; i++) {
      auto x{random_int(size.w)};
      auto y{random_int(size.h)};
      auto tile{world_area->get_tile(x, y)};
      if (tile && !tile->get_npc() &&
          tile->get_ground() != hash("GroundWater")) {
        auto new_npc = std::make_shared<npc>("NPC0");
        tile->set_npc(new_npc);
        world_area->get_npcs_mirror_ref().insert({tile->get_npc(), {x, y}});
      }
    }
  }
}