/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "calculate_new_creature_position.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  point calculate_new_creature_position(s_ptr<creature> creature) {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto &creaturesMirrorRef{worldArea->get_creatures_mirror_ref()};
    auto position{creaturesMirrorRef.at(creature)};
    auto dx{creature->get_destination().x - position.x};
    auto dy{creature->get_destination().y - position.y};
    auto normDx{normalize(dx)};
    auto normDy{normalize(dy)};
    auto newX{position.x + normDx};
    auto newY{position.y + normDy};
    return {newX, newY};
  }
}