/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_npcs.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/npc.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_npcs() {
    auto w_area{get_ston<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    auto scale{get_ston<game_properties>().k_world_scaling};
    auto num_npc_0s{200 * scale + rand_int(15 * scale)};
    for (auto i = 0; i < num_npc_0s; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && !tl->get_npc() && tl->get_ground() != hash("GroundWater")) {
        auto new_npc = std::make_shared<npc>("NPC0");
        tl->set_npc(new_npc);
        w_area->get_npcs_mirror_ref().insert({tl->get_npc(), {x, y}});
      }
    }
  }
}