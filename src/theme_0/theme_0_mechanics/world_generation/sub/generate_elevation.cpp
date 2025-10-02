/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_elevation.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_elevation() {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto size{world_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling_factor};
    auto num_hills{140 + random_int(30)};
    for (auto i = 0; i < num_hills; i++) {
      auto x_center{random_int(size.w)};
      auto y_center{random_int(size.h)};
      auto max_radius{5 * scale + random_int(5 * scale)};
      for (auto r = max_radius; r >= 0; r--) {
        for (auto y = y_center - r; y <= y_center + r; y++) {
          for (auto x = x_center - r; x <= x_center + r; x++) {
            if (!world_area->is_valid_coordinate(x, y)) {
              continue;
            }
            auto dx{x - x_center};
            auto dy{y - y_center};
            if (dx * dx + dy * dy <= r * r) {
              auto tile{world_area->get_tile(x, y)};
              if (tile && tile->get_ground() != hash("GroundWater")) {
                auto tile_n{world_area->get_tile(x, y - 1)};
                auto tile_s{world_area->get_tile(x, y + 1)};
                auto tile_w{world_area->get_tile(x - 1, y)};
                auto tile_e{world_area->get_tile(x + 1, y)};
                auto tile_nw{world_area->get_tile(x - 1, y - 1)};
                auto tile_ne{world_area->get_tile(x + 1, y - 1)};
                auto tile_sw{world_area->get_tile(x - 1, y + 1)};
                auto tile_se{world_area->get_tile(x + 1, y + 1)};
                if ((tile_n && tile_n->get_ground() == hash("GroundWater")) ||
                    (tile_s && tile_s->get_ground() == hash("GroundWater")) ||
                    (tile_w && tile_w->get_ground() == hash("GroundWater")) ||
                    (tile_e && tile_e->get_ground() == hash("GroundWater")) ||
                    (tile_nw && tile_nw->get_ground() == hash("GroundWater")) ||
                    (tile_ne && tile_ne->get_ground() == hash("GroundWater")) ||
                    (tile_sw && tile_sw->get_ground() == hash("GroundWater")) ||
                    (tile_se && tile_se->get_ground() == hash("GroundWater"))) {
                  continue;
                }
                if (tile_n && tile_n->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_s && tile_s->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_w && tile_w->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_e && tile_e->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_nw &&
                    tile_nw->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_ne &&
                    tile_ne->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_sw &&
                    tile_sw->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tile_se &&
                    tile_se->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                tile->set_elevation(tile->get_elevation() + 1);
              }
            }
          }
        }
      }
    }
  }
}