/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateCreatureMovement.hpp"
#include "sub/CalculateNewCreaturePosition.hpp"
#include "sub/GenerateNewCreatureDestination.hpp"
#include "sub/MoveCreatureToNewLocation.hpp"
#include "theme_0/theme_0_mechanics/world_structure/Creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/Tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/World.hpp"
#include "theme_0/theme_0_mechanics/world_structure/WorldArea.hpp"

namespace Forradia {
  void UpdateCreatureMovement() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};

    auto &creaturesMirrorRef{worldArea->GetCreaturesMirrorRef()};

    auto now{GetTicks()};

    for (auto it = creaturesMirrorRef.begin();
         it != creaturesMirrorRef.end();) {
      auto creature{it->first};
      auto position{it->second};

      if (now < creature->GetTicksLastMove() +
                    InvertMovementSpeed(creature->GetMovementSpeed())) {
        ++it;
        continue;
      }

      GenerateNewCreatureDestination(creature);

      auto newPosition{CalculateNewCreaturePosition(creature)};

      if (newPosition == creature->GetDestination()) {
        creature->SetDestination({-1, -1});
      }

      auto tile{worldArea->GetTile(newPosition.x, newPosition.y)};

      if (tile && !tile->GetCreature() &&
          tile->GetGround() != Hash("GroundWater")) {
        MoveCreatureToNewLocation(creature, {newPosition.x, newPosition.y});
      } else {
        creature->SetDestination({-1, -1});
      }

      ++it;
    }
  }
}