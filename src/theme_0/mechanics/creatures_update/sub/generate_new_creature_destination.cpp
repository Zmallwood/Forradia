/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_new_creature_destination.hpp"
#include "theme_0/mechanics/world_structure/creature.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_new_creature_destination(s_ptr<creature> crea) {
    auto w_area{get_ston<world>().get_current_world_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto pos{creas.at(crea)};
    auto dest{crea->get_destination()};
    if (dest.x == -1 && dest.y == -1) {
      auto new_dest{pos.x + rand_int(11) - 5};
      auto new_destination_y{pos.y + rand_int(11) - 5};
      crea->set_destination({new_dest, new_destination_y});
    }
  }
}