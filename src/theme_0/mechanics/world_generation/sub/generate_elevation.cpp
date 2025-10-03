/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_elevation.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_elevation() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling};
    auto num_hills{140 + random_int(30)};
    for (auto i = 0; i < num_hills; i++) {
      auto x_cent{random_int(sz.w)};
      auto y_cent{random_int(sz.h)};
      auto max_r{5 * scale + random_int(5 * scale)};
      for (auto r = max_r; r >= 0; r--) {
        for (auto y = y_cent - r; y <= y_cent + r; y++) {
          for (auto x = x_cent - r; x <= x_cent + r; x++) {
            if (!w_area->is_valid_coordinate(x, y)) {
              continue;
            }
            auto dx{x - x_cent};
            auto dy{y - y_cent};
            if (dx * dx + dy * dy <= r * r) {
              auto tl{w_area->get_tile(x, y)};
              if (tl && tl->get_ground() != hash("GroundWater")) {
                auto tl_n{w_area->get_tile(x, y - 1)};
                auto tl_s{w_area->get_tile(x, y + 1)};
                auto tl_w{w_area->get_tile(x - 1, y)};
                auto tl_e{w_area->get_tile(x + 1, y)};
                auto tl_nw{w_area->get_tile(x - 1, y - 1)};
                auto tl_ne{w_area->get_tile(x + 1, y - 1)};
                auto tl_sw{w_area->get_tile(x - 1, y + 1)};
                auto tl_se{w_area->get_tile(x + 1, y + 1)};
                if ((tl_n && tl_n->get_ground() == hash("GroundWater")) ||
                    (tl_s && tl_s->get_ground() == hash("GroundWater")) ||
                    (tl_w && tl_w->get_ground() == hash("GroundWater")) ||
                    (tl_e && tl_e->get_ground() == hash("GroundWater")) ||
                    (tl_nw && tl_nw->get_ground() == hash("GroundWater")) ||
                    (tl_ne && tl_ne->get_ground() == hash("GroundWater")) ||
                    (tl_sw && tl_sw->get_ground() == hash("GroundWater")) ||
                    (tl_se && tl_se->get_ground() == hash("GroundWater"))) {
                  continue;
                }
                if (tl_n && tl_n->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_s && tl_s->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_w && tl_w->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_e && tl_e->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_nw && tl_nw->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_ne && tl_ne->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_sw && tl_sw->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                if (tl_se && tl_se->get_elevation() < tl->get_elevation()) {
                  continue;
                }
                tl->set_elevation(tl->get_elevation() + 1);
              }
            }
          }
        }
      }
    }
  }
}