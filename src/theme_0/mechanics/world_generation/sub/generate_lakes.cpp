/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_lakes.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_single_lake(int min_x, int min_y, int max_x, int max_y,
                            int recurs) {
    if (recurs == 0) {
      return;
    }
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto scale{get_singleton<game_properties>().k_world_scaling};
    auto x_cent{min_x + random_int(max_x - min_x)};
    auto y_cent{min_y + random_int(max_y - min_y)};
    auto max_r{c_int(3 * scale + random_int(5 * scale))};
    for (auto r = max_r; r >= 0; r--) {
      for (auto y = y_cent - r; y <= y_cent + r; y++) {
        for (auto x = x_cent - r; x <= x_cent + r; x++) {
          auto dx{x - x_cent};
          auto dy{y - y_cent};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area->get_tile(x, y)};
            if (tl) {
              point n{x, y - 1};
              point e{x + 1, y};
              point s{x, y + 1};
              point w{x - 1, y};
              point nw{x - 1, y - 1};
              point ne{x + 1, y - 1};
              point se{x + 1, y + 1};
              point sw{x - 1, y + 1};
              point nn{x, y - 2};
              point ww{x - 2, y};
              point ee{x + 2, y};
              point ss{x, y + 2};
              point nwnw{x - 2, y - 2};
              point nene{x + 2, y - 2};
              point sese{x + 2, y + 2};
              point swsw{x - 2, y + 2};
              auto tl_n{w_area->get_tile(n)};
              auto tl_e{w_area->get_tile(e)};
              auto tl_s{w_area->get_tile(s)};
              auto tl_w{w_area->get_tile(w)};
              auto tl_nw{w_area->get_tile(nw)};
              auto tl_ne{w_area->get_tile(ne)};
              auto tl_se{w_area->get_tile(se)};
              auto tl_sw{w_area->get_tile(sw)};
              auto tl_nn{w_area->get_tile(nn)};
              auto tl_ww{w_area->get_tile(ww)};
              auto tl_ee{w_area->get_tile(ee)};
              auto tl_ss{w_area->get_tile(ss)};
              auto tl_nwnw{w_area->get_tile(nwnw)};
              auto tl_nene{w_area->get_tile(nene)};
              auto tl_sese{w_area->get_tile(sese)};
              auto tl_swsw{w_area->get_tile(swsw)};
              auto elev_n{tl_n ? tl_n->get_elevation() : 0};
              auto elev_e{tl_e ? tl_e->get_elevation() : 0};
              auto elev_s{tl_s ? tl_s->get_elevation() : 0};
              auto elev_w{tl_w ? tl_w->get_elevation() : 0};
              auto elev_nw{tl_nw ? tl_nw->get_elevation() : 0};
              auto elev_ne{tl_ne ? tl_ne->get_elevation() : 0};
              auto elev_se{tl_se ? tl_se->get_elevation() : 0};
              auto elev_sw{tl_sw ? tl_sw->get_elevation() : 0};
              auto elev_nn{tl_nn ? tl_nn->get_elevation() : 0};
              auto elev_ww{tl_ww ? tl_ww->get_elevation() : 0};
              auto elev_ee{tl_ee ? tl_ee->get_elevation() : 0};
              auto elev_ss{tl_ss ? tl_ss->get_elevation() : 0};
              auto elev_nwnw{tl_nwnw ? tl_nwnw->get_elevation() : 0};
              auto elev_nene{tl_nene ? tl_nene->get_elevation() : 0};
              auto elev_sese{tl_sese ? tl_sese->get_elevation() : 0};
              auto elev_swsw{tl_swsw ? tl_swsw->get_elevation() : 0};
              if (elev_n == 0 && elev_e == 0 && elev_s == 0 && elev_w == 0 &&
                  elev_nw == 0 && elev_ne == 0 && elev_se == 0 &&
                  elev_sw == 0 && elev_nn == 0 && elev_ww == 0 &&
                  elev_ee == 0 && elev_ss == 0 && elev_nwnw == 0 &&
                  elev_nene == 0 && elev_sese == 0 && elev_swsw == 0) {
                tl->set_ground("GroundWater");
              }
              tl->set_water_depth(tl->get_water_depth() + 1);
            }
          }
        }
      }
    }
    generate_single_lake(x_cent - max_r, y_cent - max_r, x_cent + max_r,
                         y_cent + max_r, recurs - 1);
  }

  void generate_lakes() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    auto num_lakes{20 + random_int(5)};
    for (auto i = 0; i < num_lakes; i++) {
      generate_single_lake(0, 0, sz.w, sz.h, 2 + random_int(5));
    }
  }
}