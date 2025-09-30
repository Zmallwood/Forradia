/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CalculateNewCreaturePosition.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Creature.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"

namespace Forradia {
  Point CalculateNewCreaturePosition(SharedPtr<Creature> creature) {
    auto worldArea{_<World>().GetCurrentWorldArea()};

    auto &creaturesMirrorRef{worldArea->GetCreaturesMirrorRef()};

    auto position{creaturesMirrorRef.at(creature)};

    auto dx{creature->GetDestination().x - position.x};
    auto dy{creature->GetDestination().y - position.y};

    auto normDx{Normalize(dx)};
    auto normDy{Normalize(dy)};

    auto newX{position.x + normDx};
    auto newY{position.y + normDy};

    return {newX, newY};
  }
}