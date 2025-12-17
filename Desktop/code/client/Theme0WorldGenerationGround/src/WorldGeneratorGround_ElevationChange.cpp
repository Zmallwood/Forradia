/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorGround.hpp"

namespace Forradia::Theme0 {
void WorldGeneratorGround::GenerateElevationWithBiomes() const {
  auto worldAreaSize{GetWorldAreaSize()};
  auto worldScaling{GetWorldScaling()};

  auto numMajorHills{40 + GetRandomInt(20)};

  for (auto i = 0; i < numMajorHills; i++) {
    auto xCenter{GetRandomInt(worldAreaSize.width)};
    auto yCenter{GetRandomInt(worldAreaSize.height)};
    auto radius{CInt(8 * worldScaling + GetRandomInt(12 * worldScaling))};
    auto maxElevation{30 + GetRandomInt(20)};
    CreateElevationHill(xCenter, yCenter, radius, maxElevation);
  }
}

void WorldGeneratorGround::GenerateMountainRanges() const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{GetWorldAreaSize()};
  auto worldScaling{GetWorldScaling()};

  auto numMountainRanges{3 + GetRandomInt(3)};

  for (auto range = 0; range < numMountainRanges; range++) {
    auto startX{GetRandomInt(worldAreaSize.width)};
    auto startY{GetRandomInt(worldAreaSize.height)};
    auto length{30 + GetRandomInt(40)};
    auto direction{GetRandomInt(360)};
    auto currentX{static_cast<float>(startX)};
    auto currentY{static_cast<float>(startY)};

    for (auto i = 0; i < length; i++) {
      auto x{CInt(currentX)};
      auto y{CInt(currentY)};

      if (worldArea->IsValidCoordinate(x, y)) {
        auto radius{CInt(4 * worldScaling + GetRandomInt(6 * worldScaling))};
        auto elevation{120 + GetRandomInt(160)};
        CreateElevationHill(x, y, radius, elevation);
      }

      // Move along the mountain range with some variation.
      auto angleRadians{static_cast<float>((direction + GetRandomInt(60) - 30) * M_PI / 180.0f)};

      currentX += std::cos(angleRadians) * (2.0f + GetRandomInt(3));
      currentY += std::sin(angleRadians) * (2.0f + GetRandomInt(3));

      // Occasionally change direction.
      if (GetRandomInt(100) < 20) {
        direction += GetRandomInt(60) - 30;

        if (direction < 0)
          direction += 360;

        if (direction >= 360)
          direction -= 360;
      }
    }
  }
}

void WorldGeneratorGround::GenerateValleys() const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{GetWorldAreaSize()};
  auto worldScaling{GetWorldScaling()};

  // Create valleys by reducing elevation in certain areas.
  auto numValleys{15 + GetRandomInt(10)};

  for (auto i = 0; i < numValleys; i++) {
    auto xCenter{GetRandomInt(worldAreaSize.width)};
    auto yCenter{GetRandomInt(worldAreaSize.height)};
    auto radius{CInt(10 * worldScaling + GetRandomInt(15 * worldScaling))};

    for (auto y = yCenter - radius; y <= yCenter + radius; y++) {
      for (auto x = xCenter - radius; x <= xCenter + radius; x++) {
        if (!worldArea->IsValidCoordinate(x, y))
          continue;

        auto distance{GetDistance(x, y, xCenter, yCenter)};

        if (distance > radius)
          continue;

        auto tile = worldArea->GetTile(x, y);

        if (!tile)
          continue;

        auto normalizedDistance{distance / radius};

        // Calculate the elevation reduction based on the normalized distance.
        auto elevationReduction{static_cast<int>((1.0f - normalizedDistance) * 40.0f)};

        auto currentElevation{tile->GetElevation()};
        auto newElevation{currentElevation - elevationReduction};

        // Clamp the new elevation to the valid range.
        tile->SetElevation(ClampElevation(newElevation));
      }
    }
  }
}

void WorldGeneratorGround::CreateElevationHill(int centerX, int centerY, int radius,
                                               int maxElevation) const {
  // Traverse the candidate tiles within the bounding square of the hill footprint.
  for (auto y = centerY - radius; y <= centerY + radius; y++) {
    for (auto x = centerX - radius; x <= centerX + radius; x++) {
      if (!GetWorldArea()->IsValidCoordinate(x, y))
        continue;

      auto distance{GetDistance(x, y, centerX, centerY)};

      if (distance > radius)
        continue;

      auto tile{GetWorldArea()->GetTile(x, y)};

      if (!tile)
        continue;

      if (tile->GetGround() == Hash("GroundWater"))
        continue;

      auto currentElevation{tile->GetElevation()};
      auto maxElevation{GetMaxElevation()};

      if (currentElevation >= maxElevation)
        continue;

      auto normalizedDistance{distance / radius};

      auto baseElevationGain{
          static_cast<float>((1.0f - normalizedDistance * normalizedDistance) * maxElevation)};

      // Adjust the elevation gain to avoid abrupt height increases near the peak.

      // Apply smooth falloff as we approach the elevation cap.

      // Start reducing gain when we're above 60% of max elevation for a smoother
      // transition.

      auto elevationRatio{static_cast<float>(currentElevation) / static_cast<float>(maxElevation)};

      // Start falloff at 60 % of max elevation.
      auto falloffStart{0.6f};

      auto smoothScale{1.0f};

      if (elevationRatio >= falloffStart) {
        // Smooth falloff using a smoothstep-like curve for very gradual transition.
        // When at falloffStart (60%), scale is 1.0.
        // When at 1.0 (100%), scale is 0.0.

        auto falloffRange{1.0f - falloffStart};

        // t goes from 0 to 1.
        auto t{(elevationRatio - falloffStart) / falloffRange};

        // Use smoothstep curve: 3t^2 - 2t^3 for smooth S-curve transition.
        // This gives a smoother, more natural falloff.

        smoothScale = 1.0f - (t * t * (3.0f - 2.0f * t));
      }

      // Apply smooth scaling to elevation gain.
      auto elevationGain{static_cast<int>(baseElevationGain * smoothScale)};

      if (elevationGain > 0) {
        // Calculate the target elevation before applying slope limits.
        auto desiredElevation{currentElevation + elevationGain};

        // Limit elevation based on adjacent tiles to prevent steep slopes.
        auto maxAllowedElevation{GetMaxAllowedElevation(x, y, currentElevation)};

        // Use the minimum of desired elevation and max allowed elevation.
        auto newElevation{desiredElevation};

        if (newElevation > maxAllowedElevation)
          // Respect the slope constraint when the desired elevation is too high.
          newElevation = maxAllowedElevation;

        // Final safety clamp (elevation cap and minimum).
        tile->SetElevation(ClampElevation(newElevation));
      }
    }
  }
}
}