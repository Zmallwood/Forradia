/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_creature_movement.hpp"
#include "sub/calculate_new_creature_position.hpp"
#include "sub/generate_new_creature_destination.hpp"
#include "sub/move_creature_to_new_location.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void update_creature_movement() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto &creaturesMirrorRef{worldArea->get_creatures_mirror_ref()};
    auto now{get_ticks()};
    for (auto it = creaturesMirrorRef.begin();
         it != creaturesMirrorRef.end();) {
      auto creature{it->first};
      auto position{it->second};
      if (now < creature->get_ticks_last_move() +
                    invert_movement_speed(creature->get_movement_speed())) {
        ++it;
        continue;
      }
      generate_new_creature_destination(creature);
      auto newPosition{calculate_new_creature_position(creature)};
      if (newPosition == creature->get_destination()) {
        creature->set_destination({-1, -1});
      }
      auto tile{worldArea->get_tile(newPosition.x, newPosition.y)};
      if (tile && !tile->get_creature() &&
          tile->get_ground() != hash("GroundWater")) {
        move_creature_to_new_location(creature, {newPosition.x, newPosition.y});
      } else {
        creature->set_destination({-1, -1});
      }
      ++it;
    }
  }
}