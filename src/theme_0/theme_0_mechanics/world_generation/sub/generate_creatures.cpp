/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_creatures.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_creatures() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto scale{get_singleton<game_properties>().k_worldScalingFactor};
    auto numRats{200 * scale + random_int(15 * scale)};
    for (auto i = 0; i < numRats; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && !tile->get_creature() &&
          tile->get_ground() != hash("GroundWater")) {
        auto newCreature = std::make_shared<creature>("CreatureRat");
        tile->set_creature(newCreature);
        worldArea->get_creatures_mirror_ref().insert(
            {tile->get_creature(), {x, y}});
      }
    }
  }
}