/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateNewCreatureDestination.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Creature.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"

namespace Forradia {
  void GenerateNewCreatureDestination(SharedPtr<Creature> creature) {
    auto worldArea{_<World>().GetCurrentWorldArea()};

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