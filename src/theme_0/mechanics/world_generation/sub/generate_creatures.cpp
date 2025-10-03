/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_creatures.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/creature.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_creatures() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling};
    auto num_rats{200 * scale + random_int(15 * scale)};
    for (auto i = 0; i < num_rats; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        auto new_crea = std::make_shared<creature>("CreatureRat");
        tl->set_creature(new_crea);
        w_area->get_creatures_mirror_ref().insert({tl->get_creature(), {x, y}});
      }
    }
    auto num_butterflies{200 * scale + random_int(15 * scale)};
    for (auto i = 0; i < num_butterflies; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && !tl->get_creature() &&
          tl->get_ground() != hash("GroundWater")) {
        auto new_crea = std::make_shared<creature>("CreatureButterfly");
        tl->set_creature(new_crea);
        w_area->get_creatures_mirror_ref().insert({tl->get_creature(), {x, y}});
      }
    }
  }
}