/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateCreatures.hpp"
#include "theme_0/theme_0_mechanics/configuration/GameProperties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/Creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/Tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/World.hpp"
#include "theme_0/theme_0_mechanics/world_structure/WorldArea.hpp"

namespace Forradia {
  void GenerateCreatures() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};

    auto size{worldArea->GetSize()};

    auto scale{GetSingleton<GameProperties>().k_worldScalingFactor};

    auto numRats{200 * scale + RandomInt(15 * scale)};

    for (auto i = 0; i < numRats; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && !tile->GetCreature() &&
          tile->GetGround() != Hash("GroundWater")) {
        auto newCreature = std::make_shared<Creature>("CreatureRat");
        tile->SetCreature(newCreature);
        worldArea->GetCreaturesMirrorRef().insert(
            {tile->GetCreature(), {x, y}});
      }
    }
  }
}