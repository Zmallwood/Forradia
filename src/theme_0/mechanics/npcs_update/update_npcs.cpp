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
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto &npcs_mirror_ref{world_area->get_npcs_mirror_ref()};
    auto now{get_ticks()};
    for (auto it = npcs_mirror_ref.begin(); it != npcs_mirror_ref.end();) {
      auto npc{it->first};
      auto position{it->second};

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
      auto destination{npc->get_destination()};
      if (destination.x == -1 && destination.y == -1) {
        auto new_destination_x{position.x + random_int(11) - 5};
        auto new_destination_y{position.y + random_int(11) - 5};
        npc->set_destination({new_destination_x, new_destination_y});
      }
      auto dx{npc->get_destination().x - position.x};
      auto dy{npc->get_destination().y - position.y};
      auto norm_dx{normalize(dx)};
      auto norm_dy{normalize(dy)};
      auto new_x{position.x + norm_dx};
      auto new_y{position.y + norm_dy};
      auto new_position{point{new_x, new_y}};
      if (new_position == npc->get_destination()) {
        npc->set_destination({-1, -1});
      }
      auto tile{world_area->get_tile(new_position.x, new_position.y)};
      if (tile && !tile->get_npc() &&
          tile->get_ground() != hash("GroundWater")) {
        auto old_position{position};
        npc->set_ticks_last_move(now);
        auto old_tile{world_area->get_tile(old_position.x, old_position.y)};
        auto new_tile{world_area->get_tile(new_position.x, new_position.y)};
        old_tile->set_npc(nullptr);
        new_tile->set_npc(npc);
        npcs_mirror_ref.erase(npc);
        npcs_mirror_ref.insert({npc, {new_position.x, new_position.y}});
      } else {
        npc->set_destination({-1, -1});
      }
      ++it;
    }
  }
}