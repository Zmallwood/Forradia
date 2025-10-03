/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_rock.hpp"
#include "theme_0/func/game_props.hpp"
#include "world_struct.hpp"

namespace forr {
  void gen_rock() {
    auto w_area{_<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto scale{_<game_props>().k_world_scaling};
    auto num_rock_areas{30 + rand_int(10)};
    for (auto i = 0; i < num_rock_areas; i++) {
      auto x_center{rand_int(sz.w)};
      auto y_center{rand_int(sz.h)};
      auto r{3 * scale + rand_int(10 * scale)};
      for (auto y = y_center - r; y <= y_center + r; y++) {
        for (auto x = x_center - r; x <= x_center + r; x++) {
          if (!w_area->is_valid_coord(x, y)) {
            continue;
          }
          auto dx{x - x_center};
          auto dy{y - y_center};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area->get_tl(x, y)};
            if (tl->get_elev() > 0) {
              tl->set_ground("GroundRock");
            }
          }
        }
      }
    }
  }
}