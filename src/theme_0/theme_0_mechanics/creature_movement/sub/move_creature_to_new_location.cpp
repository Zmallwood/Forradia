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
                                     point newPosition) {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto &creaturesMirrorRef{worldArea->get_creatures_mirror_ref()};
    auto oldPosition{creaturesMirrorRef.at(creature)};
    auto now{get_ticks()};
    creature->set_ticks_last_move(now);
    auto oldTile{worldArea->get_tile(oldPosition.x, oldPosition.y)};
    auto newTile{worldArea->get_tile(newPosition.x, newPosition.y)};
    oldTile->set_creature(nullptr);
    newTile->set_creature(creature);
    creaturesMirrorRef.erase(creature);
    creaturesMirrorRef.insert({creature, {newPosition.x, newPosition.y}});
  }
}