/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "WorldGeneratorEntities.hpp"
#include "Entity.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
  auto WorldGeneratorEntities::GenerateEntities() const -> void {
    GenerateEntitiesInEcosystems();
  }

  auto WorldGeneratorEntities::IsNearWater(int x, int y, int radius) const -> bool {
    for (auto checkY = y - radius; checkY <= y + radius; checkY++) {
      for (auto checkX = x - radius; checkX <= x + radius; checkX++) {
        if (!GetWorldArea()->IsValidCoordinate(checkX, checkY))
          continue;

        auto tile{GetWorldArea()->GetTile(checkX, checkY)};

        if (tile && tile->GetGround() == Hash("GroundWater")) {
          auto distance{GetDistance(x, y, checkX, checkY)};

          if (distance <= radius)
            return true;
        }
      }
    }

    return false;
  }
}
