/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_creas.hpp"
#include "theme_0/func/game_props.hpp"
#include "theme_0/func/world_struct.hpp"

namespace forr {
  void gen_creas() {
    auto w_area{_<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto scale{_<game_props>().k_world_scaling};
    auto num_rats{200 * scale + rand_int(15 * scale)};
    for (auto i = 0; i < num_rats; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        auto new_crea = std::make_shared<creature>("CreatureRat");
        tl->set_creature(new_crea);
        w_area->get_creatures_mirror_ref().insert({tl->get_creature(), {x, y}});
      }
    }
    auto num_butterflies{200 * scale + rand_int(15 * scale)};
    for (auto i = 0; i < num_butterflies; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        auto new_crea = std::make_shared<creature>("CreatureButterfly");
        tl->set_creature(new_crea);
        w_area->get_creatures_mirror_ref().insert({tl->get_creature(), {x, y}});
      }
    }
  }
}