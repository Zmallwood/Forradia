/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_crea_movem.hpp"
#include "theme_0/func/world_struct/creature.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void update_crea_movem() {
    auto w_area{_<world>().get_curr_w_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto now{get_ticks()};
    for (auto it = creas.begin(); it != creas.end();) {
      auto crea{it->first};
      auto pos{it->second};
      if (now <
          crea->get_ticks_last_move() + inv_movem_spd(crea->get_movem_spd())) {
        ++it;
        continue;
      }
      auto dest{crea->get_dest()};
      if (dest.x == -1 && dest.y == -1) {
        auto new_dest{pos.x + rand_int(11) - 5};
        auto new_destination_y{pos.y + rand_int(11) - 5};
        crea->set_dest({new_dest, new_destination_y});
      }
      auto w_area{_<world>().get_curr_w_area()};
      auto &creas{w_area->get_creatures_mirror_ref()};
      auto dx{crea->get_dest().x - pos.x};
      auto dy{crea->get_dest().y - pos.y};
      auto norm_dx{normalize(dx)};
      auto norm_dy{normalize(dy)};
      auto new_x{pos.x + norm_dx};
      auto new_y{pos.y + norm_dy};
      point new_pos{new_x, new_y};
      if (new_pos == crea->get_dest()) {
        crea->set_dest({-1, -1});
      }
      auto tl{w_area->get_tl(new_pos.x, new_pos.y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        auto old_pos{creas.at(crea)};
        crea->set_ticks_last_move(now);
        auto old_tile{w_area->get_tl(old_pos.x, old_pos.y)};
        auto new_tile{w_area->get_tl(new_pos.x, new_pos.y)};
        old_tile->set_creature(nullptr);
        new_tile->set_creature(crea);
        creas.erase(crea);
        creas.insert({crea, {new_pos.x, new_pos.y}});
      } else {
        crea->set_dest({-1, -1});
      }
      ++it;
    }
  }
}