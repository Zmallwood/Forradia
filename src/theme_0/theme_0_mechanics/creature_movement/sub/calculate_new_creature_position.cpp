/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "calculate_new_creature_position.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  point CalculateNewCreaturePosition(s_ptr<creature> creature) {
    auto worldArea{GetSingleton<world>().GetCurrentWorldArea()};
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