/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_npcs.hpp"
#include "theme_0/func/conf/game_props.hpp"
#include "theme_0/func/world_struct/npc.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void gen_npcs() {
    auto w_area{_<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto scale{_<game_props>().k_world_scaling};
    auto num_npc_0s{200 * scale + rand_int(15 * scale)};
    for (auto i = 0; i < num_npc_0s; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && !tl->get_npc() && tl->get_ground() != hash("GroundWater")) {
        auto new_npc = std::make_shared<npc>("NPC0");
        tl->set_npc(new_npc);
        w_area->get_npcs_mirror_ref().insert({tl->get_npc(), {x, y}});
      }
    }
  }
}