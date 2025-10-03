/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "calc_new_crea_pos.hpp"
#include "theme_0/func/world_structure/creature.hpp"
#include "theme_0/func/world_structure/world.hpp"
#include "theme_0/func/world_structure/world_area.hpp"

namespace forr {
  point calc_new_crea_pos(s_ptr<creature> crea) {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto &creas{w_area->get_creatures_mirror_ref()};
    auto pos{creas.at(crea)};
    auto dx{crea->get_dest().x - pos.x};
    auto dy{crea->get_dest().y - pos.y};
    auto norm_dx{normalize(dx)};
    auto norm_dy{normalize(dy)};
    auto new_x{pos.x + norm_dx};
    auto new_y{pos.y + norm_dy};
    return {new_x, new_y};
  }
}