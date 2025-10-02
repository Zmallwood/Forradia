/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "calculate_new_creature_position.hpp"
#include "theme_0/mechanics/world_structure/creature.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  point calculate_new_creature_position(s_ptr<creature> creature) {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto &creatures_mirror_ref{world_area->get_creatures_mirror_ref()};
    auto position{creatures_mirror_ref.at(creature)};
    auto dx{creature->get_destination().x - position.x};
    auto dy{creature->get_destination().y - position.y};
    auto norm_dx{normalize(dx)};
    auto norm_dy{normalize(dy)};
    auto new_x{position.x + norm_dx};
    auto new_y{position.y + norm_dy};
    return {new_x, new_y};
  }
}