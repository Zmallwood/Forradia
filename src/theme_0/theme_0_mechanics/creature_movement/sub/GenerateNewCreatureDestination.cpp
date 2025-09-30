/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateNewCreatureDestination.hpp"
#include "theme_0/theme_0_mechanics/world_structure/Creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/World.hpp"
#include "theme_0/theme_0_mechanics/world_structure/WorldArea.hpp"

namespace Forradia {
  void GenerateNewCreatureDestination(SharedPtr<Creature> creature) {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};

    auto &creaturesMirrorRef{worldArea->GetCreaturesMirrorRef()};

    auto position{creaturesMirrorRef.at(creature)};

    auto destination{creature->GetDestination()};

    if (destination.x == -1 && destination.y == -1) {
      auto newDestinationX{position.x + RandomInt(11) - 5};
      auto newDestinationY{position.y + RandomInt(11) - 5};

      creature->SetDestination({newDestinationX, newDestinationY});
    }
  }
}