/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_crea_movem.hpp"
#include "sub/calc_new_crea_pos.hpp"
#include "sub/gen_new_crea_dest.hpp"
#include "sub/move_crea_to_new_loc.hpp"
#include "theme_0/func/world_struct/creature.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void update_crea_movem() {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto now{get_ticks()};
    for (auto it = creas.begin(); it != creas.end();) {
      auto crea{it->first};
      auto pos{it->second};
      if (now < crea->get_ticks_last_move() +
                    inv_movem_spd(crea->get_movem_spd())) {
        ++it;
        continue;
      }
      gen_new_crea_dest(crea);
      auto new_pos{calc_new_crea_pos(crea)};
      if (new_pos == crea->get_dest()) {
        crea->set_dest({-1, -1});
      }
      auto tl{w_area->get_tl(new_pos.x, new_pos.y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        move_crea_to_new_loc(crea, {new_pos.x, new_pos.y});
      } else {
        crea->set_dest({-1, -1});
      }
      ++it;
    }
  }
}