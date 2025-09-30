/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MoveCreatureToNewLocation.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Creature.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"

namespace Forradia {
  void MoveCreatureToNewLocation(SharedPtr<Creature> creature,
                                 Point newPosition) {
    auto worldArea{_<World>().GetCurrentWorldArea()};

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