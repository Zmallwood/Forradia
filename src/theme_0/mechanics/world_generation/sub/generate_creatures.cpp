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
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto size{world_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling_factor};
    auto num_rats{200 * scale + random_int(15 * scale)};
    for (auto i = 0; i < num_rats; i++) {
      auto x{random_int(size.w)};
      auto y{random_int(size.h)};
      auto tile{world_area->get_tile(x, y)};
      if (tile && !tile->get_creature() &&
          tile->get_ground() != hash("GroundWater")) {
        auto new_creature = std::make_shared<creature>("CreatureRat");
        tile->set_creature(new_creature);
        world_area->get_creatures_mirror_ref().insert(
            {tile->get_creature(), {x, y}});
      }
    }
  }
}