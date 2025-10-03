/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "calculate_new_creature_position.hpp"
#include "theme_0/mechanics/world_structure/creature.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  point calculate_new_creature_position(s_ptr<creature> crea) {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto pos{creas.at(crea)};
    auto dx{crea->get_destination().x - pos.x};
    auto dy{crea->get_destination().y - pos.y};
    auto norm_dx{normalize(dx)};
    auto norm_dy{normalize(dy)};
    auto new_x{pos.x + norm_dx};
    auto new_y{pos.y + norm_dy};
    return {new_x, new_y};
  }
}