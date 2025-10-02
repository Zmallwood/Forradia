/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_lakes.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_single_lake(int min_x, int min_y, int max_x, int max_y,
                            int recursive) {
    if (recursive == 0) {
      return;
    }
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto scale{get_singleton<game_properties>().k_world_scaling_factor};
    auto x_center{min_x + random_int(max_x - min_x)};
    auto y_center{min_y + random_int(max_y - min_y)};
    auto radius{c_int(3 * scale + random_int(5 * scale))};
    for (auto r = radius; r >= 0; r--) {
      for (auto y = y_center - r; y <= y_center + r; y++) {
        for (auto x = x_center - r; x <= x_center + r; x++) {
          auto dx{x - x_center};
          auto dy{y - y_center};
          if (dx * dx + dy * dy <= r * r) {
            auto tile{world_area->get_tile(x, y)};
            if (tile) {
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
              auto tile_n{world_area->get_tile(n)};
              auto tile_e{world_area->get_tile(e)};
              auto tile_s{world_area->get_tile(s)};
              auto tile_w{world_area->get_tile(w)};
              auto tile_nw{world_area->get_tile(nw)};
              auto tile_ne{world_area->get_tile(ne)};
              auto tile_se{world_area->get_tile(se)};
              auto tile_sw{world_area->get_tile(sw)};
              auto tile_nn{world_area->get_tile(nn)};
              auto tile_ww{world_area->get_tile(ww)};
              auto tile_ee{world_area->get_tile(ee)};
              auto tile_ss{world_area->get_tile(ss)};
              auto tile_nwnw{world_area->get_tile(nwnw)};
              auto tile_nene{world_area->get_tile(nene)};
              auto tile_sese{world_area->get_tile(sese)};
              auto tile_swsw{world_area->get_tile(swsw)};
              auto elev_n{tile_n ? tile_n->get_elevation() : 0};
              auto elev_e{tile_e ? tile_e->get_elevation() : 0};
              auto elev_s{tile_s ? tile_s->get_elevation() : 0};
              auto elev_w{tile_w ? tile_w->get_elevation() : 0};
              auto elev_nw{tile_nw ? tile_nw->get_elevation() : 0};
              auto elev_ne{tile_ne ? tile_ne->get_elevation() : 0};
              auto elev_se{tile_se ? tile_se->get_elevation() : 0};
              auto elev_sw{tile_sw ? tile_sw->get_elevation() : 0};
              auto elev_nn{tile_nn ? tile_nn->get_elevation() : 0};
              auto elev_ww{tile_ww ? tile_ww->get_elevation() : 0};
              auto elev_ee{tile_ee ? tile_ee->get_elevation() : 0};
              auto elev_ss{tile_ss ? tile_ss->get_elevation() : 0};
              auto elev_nwnw{tile_nwnw ? tile_nwnw->get_elevation() : 0};
              auto elev_nene{tile_nene ? tile_nene->get_elevation() : 0};
              auto elev_sese{tile_sese ? tile_sese->get_elevation() : 0};
              auto elev_swsw{tile_swsw ? tile_swsw->get_elevation() : 0};
              if (elev_n == 0 && elev_e == 0 && elev_s == 0 && elev_w == 0 &&
                  elev_nw == 0 && elev_ne == 0 && elev_se == 0 &&
                  elev_sw == 0 && elev_nn == 0 && elev_ww == 0 &&
                  elev_ee == 0 && elev_ss == 0 && elev_nwnw == 0 &&
                  elev_nene == 0 && elev_sese == 0 && elev_swsw == 0) {
                tile->set_ground("GroundWater");
              }
              tile->set_water_depth(tile->get_water_depth() + 1);
            }
          }
        }
      }
    }
    generate_single_lake(x_center - radius, y_center - radius,
                         x_center + radius, y_center + radius, recursive - 1);
  }

  void generate_lakes() {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto size{world_area->get_size()};
    auto num_lakes{20 + random_int(5)};
    for (auto i = 0; i < num_lakes; i++) {
      generate_single_lake(0, 0, size.w, size.h, 2 + random_int(5));
    }
  }
}