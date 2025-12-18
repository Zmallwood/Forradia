/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "StdAfx.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorGround.hpp"

namespace Forradia::Theme0 {
  auto WorldGeneratorGround::GenerateGrassBiomes() const -> void {
    auto worldArea{GetWorldArea()};
    auto worldAreaSize{GetWorldAreaSize()};
    auto worldScaling{GetWorldScaling()};

    // Create distinct grass biomes with organic shapes.
    // Grass appears in areas with moderate elevation (not mountains, not deep valleys).

    auto numGrassBiomes{25 + GetRandomInt(15)};

    for (auto i = 0; i < numGrassBiomes; i++) {
      auto xCenter{GetRandomInt(worldAreaSize.width)};
      auto yCenter{GetRandomInt(worldAreaSize.height)};

      auto tile{worldArea->GetTile(xCenter, yCenter)};

      // Check if this area is suitable for grass (moderate elevation, not water).
      if (!tile || tile->GetElevation() > 100 || tile->GetGround() == Hash("GroundWater"))
        continue;

      auto radius{CInt(6 * worldScaling + GetRandomInt(10 * worldScaling))};
      auto density{0.7F + GetRandomInt(30) / 100.0F}; // 0.7 to 1.0.
      CreateBiomeCluster(xCenter, yCenter, radius, "GroundGrass");
    }

    // Also add grass in valleys and low-lying areas naturally.

    for (auto y = 0; y < worldAreaSize.height; y++) {
      for (auto x = 0; x < worldAreaSize.width; x++) {
        auto tile = worldArea->GetTile(x, y);

        if (!tile)
          continue;

        // Grass naturally grows in low-lying areas that aren't water.
        if (tile->GetElevation() <= 20 && tile->GetGround() != Hash("GroundWater") &&
            tile->GetGround() != Hash("GroundRock"))
          tile->SetGround("GroundGrass");
      }
    }
  }

  auto WorldGeneratorGround::GenerateRockFormations() const -> void {
    auto worldArea{GetWorldArea()};
    auto worldAreaSize{GetWorldAreaSize()};
    auto worldScaling{GetWorldScaling()};

    auto numRockFormations{20 + GetRandomInt(15)};

    for (auto i = 0; i < numRockFormations; i++) {
      auto xCenter{GetRandomInt(worldAreaSize.width)};
      auto yCenter{GetRandomInt(worldAreaSize.height)};

      auto tile{worldArea->GetTile(xCenter, yCenter)};

      if (!tile || tile->GetElevation() < 80)
        continue;

      // Create rock formations on high elevation.

      auto radius{CInt(2 * worldScaling + GetRandomInt(5 * worldScaling))};

      for (auto y = yCenter - radius; y <= yCenter + radius; y++) {
        for (auto x = xCenter - radius; x <= xCenter + radius; x++) {
          if (!worldArea->IsValidCoordinate(x, y))
            continue;

          auto distance{GetDistance(x, y, xCenter, yCenter)};

          if (distance > radius)
            continue;

          auto rockTile{worldArea->GetTile(x, y)};

          // Skip if the tile is not found or the ground is water.

          if (!rockTile || rockTile->GetGround() == Hash("GroundWater"))
            continue;

          // Place rocks on mountain peaks and high elevation areas. Higher elevation =
          // more likely to be rock.

          auto elevation{rockTile->GetElevation()};

          if (elevation > 60)
            rockTile->SetGround("GroundRock");
        }
      }
    }
  }

  auto WorldGeneratorGround::CreateBiomeCluster(int centerX, int centerY, int radius,
                                                StringView groundType) const -> void {
    // Enumerate all tiles in the radius.
    for (auto y = centerY - radius; y <= centerY + radius; y++) {
      for (auto x = centerX - radius; x <= centerX + radius; x++) {
        if (!GetWorldArea()->IsValidCoordinate(x, y))
          continue;

        auto distance{GetDistance(x, y, centerX, centerY)};

        if (distance > radius)
          continue;

        auto tile{GetWorldArea()->GetTile(x, y)};

        if (tile)
          tile->SetGround(groundType);
      }
    }
  }
}
