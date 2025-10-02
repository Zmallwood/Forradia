/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_new_creature_destination.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_new_creature_destination(s_ptr<creature> creature) {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto &creatures_mirror_ref{world_area->get_creatures_mirror_ref()};
    auto position{creatures_mirror_ref.at(creature)};
    auto destination{creature->get_destination()};
    if (destination.x == -1 && destination.y == -1) {
      auto new_destination_x{position.x + random_int(11) - 5};
      auto new_destination_y{position.y + random_int(11) - 5};
      creature->set_destination({new_destination_x, new_destination_y});
    }
  }
}