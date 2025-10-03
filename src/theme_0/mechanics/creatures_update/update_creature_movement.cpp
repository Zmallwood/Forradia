/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_creature_movement.hpp"
#include "sub/calculate_new_creature_position.hpp"
#include "sub/generate_new_creature_destination.hpp"
#include "sub/move_creature_to_new_location.hpp"
#include "theme_0/mechanics/world_structure/creature.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void update_creature_movement() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto now{get_ticks()};
    for (auto it = creas.begin(); it != creas.end();) {
      auto crea{it->first};
      auto pos{it->second};
      if (now < crea->get_ticks_last_move() +
                    invert_movement_speed(crea->get_movement_speed())) {
        ++it;
        continue;
      }
      generate_new_creature_destination(crea);
      auto new_pos{calculate_new_creature_position(crea)};
      if (new_pos == crea->get_destination()) {
        crea->set_destination({-1, -1});
      }
      auto tl{w_area->get_tile(new_pos.x, new_pos.y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        move_creature_to_new_location(crea, {new_pos.x, new_pos.y});
      } else {
        crea->set_destination({-1, -1});
      }
      ++it;
    }
  }
}