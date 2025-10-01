/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_new_creature_destination.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void GenerateNewCreatureDestination(s_ptr<Creature> creature) {
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