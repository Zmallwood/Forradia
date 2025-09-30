/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "move_creature_to_new_location.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace Forradia {
  void MoveCreatureToNewLocation(SharedPtr<Creature> creature,
                                 Point newPosition) {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};
    auto &creaturesMirrorRef{worldArea->GetCreaturesMirrorRef()};
    auto oldPosition{creaturesMirrorRef.at(creature)};
    auto now{GetTicks()};
    creature->SetTicksLastMove(now);
    auto oldTile{worldArea->GetTile(oldPosition.x, oldPosition.y)};
    auto newTile{worldArea->GetTile(newPosition.x, newPosition.y)};
    oldTile->SetCreature(nullptr);
    newTile->SetCreature(creature);
    creaturesMirrorRef.erase(creature);
    creaturesMirrorRef.insert({creature, {newPosition.x, newPosition.y}});
  }
}