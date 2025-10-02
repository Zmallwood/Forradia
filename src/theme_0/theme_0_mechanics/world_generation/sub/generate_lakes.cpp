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
  void generate_single_lake(int minX, int minY, int maxX, int maxY,
                            int recursive) {
    if (recursive == 0) {
      return;
    }
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto scale{get_singleton<game_properties>().k_worldScalingFactor};
    auto xCenter{minX + random_int(maxX - minX)};
    auto yCenter{minY + random_int(maxY - minY)};
    auto radius{c_int(3 * scale + random_int(5 * scale))};
    for (auto r = radius; r >= 0; r--) {
      for (auto y = yCenter - r; y <= yCenter + r; y++) {
        for (auto x = xCenter - r; x <= xCenter + r; x++) {
          auto dx{x - xCenter};
          auto dy{y - yCenter};
          if (dx * dx + dy * dy <= r * r) {
            auto tile{worldArea->get_tile(x, y)};
            if (tile) {
              point N{x, y - 1};
              point E{x + 1, y};
              point S{x, y + 1};
              point W{x - 1, y};
              point NW{x - 1, y - 1};
              point NE{x + 1, y - 1};
              point SE{x + 1, y + 1};
              point SW{x - 1, y + 1};
              point NN{x, y - 2};
              point WW{x - 2, y};
              point EE{x + 2, y};
              point SS{x, y + 2};
              point NWNW{x - 2, y - 2};
              point NENE{x + 2, y - 2};
              point SESE{x + 2, y + 2};
              point SWSW{x - 2, y + 2};
              auto tileN{worldArea->get_tile(N)};
              auto tileE{worldArea->get_tile(E)};
              auto tileS{worldArea->get_tile(S)};
              auto tileW{worldArea->get_tile(W)};
              auto tileNW{worldArea->get_tile(NW)};
              auto tileNE{worldArea->get_tile(NE)};
              auto tileSE{worldArea->get_tile(SE)};
              auto tileSW{worldArea->get_tile(SW)};
              auto tileNN{worldArea->get_tile(NN)};
              auto tileWW{worldArea->get_tile(WW)};
              auto tileEE{worldArea->get_tile(EE)};
              auto tileSS{worldArea->get_tile(SS)};
              auto tileNWNW{worldArea->get_tile(NWNW)};
              auto tileNENE{worldArea->get_tile(NENE)};
              auto tileSESE{worldArea->get_tile(SESE)};
              auto tileSWSW{worldArea->get_tile(SWSW)};
              auto elevationN{tileN ? tileN->get_elevation() : 0};
              auto elevationE{tileE ? tileE->get_elevation() : 0};
              auto elevationS{tileS ? tileS->get_elevation() : 0};
              auto elevationW{tileW ? tileW->get_elevation() : 0};
              auto elevationNW{tileNW ? tileNW->get_elevation() : 0};
              auto elevationNE{tileNE ? tileNE->get_elevation() : 0};
              auto elevationSE{tileSE ? tileSE->get_elevation() : 0};
              auto elevationSW{tileSW ? tileSW->get_elevation() : 0};
              auto elevationNN{tileNN ? tileNN->get_elevation() : 0};
              auto elevationWW{tileWW ? tileWW->get_elevation() : 0};
              auto elevationEE{tileEE ? tileEE->get_elevation() : 0};
              auto elevationSS{tileSS ? tileSS->get_elevation() : 0};
              auto elevationNWNW{tileNWNW ? tileNWNW->get_elevation() : 0};
              auto elevationNENE{tileNENE ? tileNENE->get_elevation() : 0};
              auto elevationSESE{tileSESE ? tileSESE->get_elevation() : 0};
              auto elevationSWSW{tileSWSW ? tileSWSW->get_elevation() : 0};
              if (elevationN == 0 && elevationE == 0 && elevationS == 0 &&
                  elevationW == 0 && elevationNW == 0 && elevationNE == 0 &&
                  elevationSE == 0 && elevationSW == 0 && elevationNN == 0 &&
                  elevationWW == 0 && elevationEE == 0 && elevationSS == 0 &&
                  elevationNWNW == 0 && elevationNENE == 0 &&
                  elevationSESE == 0 && elevationSWSW == 0) {
                tile->set_ground("GroundWater");
              }
              tile->set_water_depth(tile->get_water_depth() + 1);
            }
          }
        }
      }
    }
    generate_single_lake(xCenter - radius, yCenter - radius, xCenter + radius,
                         yCenter + radius, recursive - 1);
  }

  void generate_lakes() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto numLakes{20 + random_int(5)};
    for (auto i = 0; i < numLakes; i++) {
      generate_single_lake(0, 0, size.w, size.h, 2 + random_int(5));
    }
  }
}