/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "move_creature_to_new_location.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void move_creature_to_new_location(s_ptr<creature> creature,
                                     point new_position) {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto &creatures_mirror_ref{world_area->get_creatures_mirror_ref()};
    auto old_position{creatures_mirror_ref.at(creature)};
    auto now{get_ticks()};
    creature->set_ticks_last_move(now);
    auto old_tile{world_area->get_tile(old_position.x, old_position.y)};
    auto new_tile{world_area->get_tile(new_position.x, new_position.y)};
    old_tile->set_creature(nullptr);
    new_tile->set_creature(creature);
    creatures_mirror_ref.erase(creature);
    creatures_mirror_ref.insert({creature, {new_position.x, new_position.y}});
  }
}