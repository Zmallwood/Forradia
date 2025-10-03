/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_new_crea_dest.hpp"
#include "theme_0/func/world_struct/creature.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void gen_new_crea_dest(s_ptr<creature> crea) {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto pos{creas.at(crea)};
    auto dest{crea->get_dest()};
    if (dest.x == -1 && dest.y == -1) {
      auto new_dest{pos.x + rand_int(11) - 5};
      auto new_destination_y{pos.y + rand_int(11) - 5};
      crea->set_dest({new_dest, new_destination_y});
    }
  }
}