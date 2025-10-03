/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_lakes.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void gen_single_lake(int min_x, int min_y, int max_x, int max_y, int recurs) {
    if (recurs == 0) {
      return;
    }
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto scale{get_ston<game_properties>().k_world_scaling};
    auto x_cent{min_x + rand_int(max_x - min_x)};
    auto y_cent{min_y + rand_int(max_y - min_y)};
    auto max_r{c_int(3 * scale + rand_int(5 * scale))};
    for (auto r = max_r; r >= 0; r--) {
      for (auto y = y_cent - r; y <= y_cent + r; y++) {
        for (auto x = x_cent - r; x <= x_cent + r; x++) {
          auto dx{x - x_cent};
          auto dy{y - y_cent};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area->get_tl(x, y)};
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
              auto tl_n{w_area->get_tl(n)};
              auto tl_e{w_area->get_tl(e)};
              auto tl_s{w_area->get_tl(s)};
              auto tl_w{w_area->get_tl(w)};
              auto tl_nw{w_area->get_tl(nw)};
              auto tl_ne{w_area->get_tl(ne)};
              auto tl_se{w_area->get_tl(se)};
              auto tl_sw{w_area->get_tl(sw)};
              auto tl_nn{w_area->get_tl(nn)};
              auto tl_ww{w_area->get_tl(ww)};
              auto tl_ee{w_area->get_tl(ee)};
              auto tl_ss{w_area->get_tl(ss)};
              auto tl_nwnw{w_area->get_tl(nwnw)};
              auto tl_nene{w_area->get_tl(nene)};
              auto tl_sese{w_area->get_tl(sese)};
              auto tl_swsw{w_area->get_tl(swsw)};
              auto elev_n{tl_n ? tl_n->get_elev() : 0};
              auto elev_e{tl_e ? tl_e->get_elev() : 0};
              auto elev_s{tl_s ? tl_s->get_elev() : 0};
              auto elev_w{tl_w ? tl_w->get_elev() : 0};
              auto elev_nw{tl_nw ? tl_nw->get_elev() : 0};
              auto elev_ne{tl_ne ? tl_ne->get_elev() : 0};
              auto elev_se{tl_se ? tl_se->get_elev() : 0};
              auto elev_sw{tl_sw ? tl_sw->get_elev() : 0};
              auto elev_nn{tl_nn ? tl_nn->get_elev() : 0};
              auto elev_ww{tl_ww ? tl_ww->get_elev() : 0};
              auto elev_ee{tl_ee ? tl_ee->get_elev() : 0};
              auto elev_ss{tl_ss ? tl_ss->get_elev() : 0};
              auto elev_nwnw{tl_nwnw ? tl_nwnw->get_elev() : 0};
              auto elev_nene{tl_nene ? tl_nene->get_elev() : 0};
              auto elev_sese{tl_sese ? tl_sese->get_elev() : 0};
              auto elev_swsw{tl_swsw ? tl_swsw->get_elev() : 0};
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
    gen_single_lake(x_cent - max_r, y_cent - max_r, x_cent + max_r,
                    y_cent + max_r, recurs - 1);
  }

  void gen_lakes() {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto num_lakes{20 + rand_int(5)};
    for (auto i = 0; i < num_lakes; i++) {
      gen_single_lake(0, 0, sz.w, sz.h, 2 + rand_int(5));
    }
  }
}