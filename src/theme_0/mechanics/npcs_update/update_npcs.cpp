/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_npcs.hpp"
#include "core/gui/gui_text_console.hpp"
#include "theme_0/mechanics/world_structure/npc.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void update_npcs() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto &npcs{w_area->get_npcs_mirror_ref()};
    auto now{get_ticks()};
    for (auto it = npcs.begin(); it != npcs.end();) {
      auto npc{it->first};
      auto pos{it->second};

      if (now > npc->get_ticks_next_spontaneous_speech()) {
        auto name{npc->get_name()};
        if (random_int(20) == 0) {
          get_singleton<gui_text_console>().print(
              name + ": Buying blueberries, one gold each.");
        } else {
          get_singleton<gui_text_console>().print(name + ": Hello all!");
        }
        npc->set_ticks_next_spontaneous_speech(now + 5 * k_one_second_millis +
                                               (6000 * k_one_second_millis));
      }

      if (now < npc->get_ticks_last_move() +
                    invert_movement_speed(npc->get_movement_speed())) {
        ++it;
        continue;
      }
      auto dest{npc->get_destination()};
      if (dest.x == -1 && dest.y == -1) {
        auto new_dest_x{pos.x + random_int(11) - 5};
        auto new_dest_y{pos.y + random_int(11) - 5};
        npc->set_destination({new_dest_x, new_dest_y});
      }
      auto dx{npc->get_destination().x - pos.x};
      auto dy{npc->get_destination().y - pos.y};
      auto norm_dx{normalize(dx)};
      auto norm_dy{normalize(dy)};
      auto new_x{pos.x + norm_dx};
      auto new_y{pos.y + norm_dy};
      auto new_pos{point{new_x, new_y}};
      if (new_pos == npc->get_destination()) {
        npc->set_destination({-1, -1});
      }
      auto tl{w_area->get_tile(new_pos.x, new_pos.y)};
      if (tl && !tl->get_npc() && tl->get_ground() != hash("GroundWater")) {
        auto old_pos{pos};
        npc->set_ticks_last_move(now);
        auto old_tl{w_area->get_tile(old_pos.x, old_pos.y)};
        auto new_tl{w_area->get_tile(new_pos.x, new_pos.y)};
        old_tl->set_npc(nullptr);
        new_tl->set_npc(npc);
        npcs.erase(npc);
        npcs.insert({npc, {new_pos.x, new_pos.y}});
      } else {
        npc->set_destination({-1, -1});
      }
      ++it;
    }
  }
}