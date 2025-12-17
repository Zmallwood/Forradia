/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0 {
/**
 * World generator for water.
 */
class WorldGeneratorWater : public WorldGeneratorBase {
 public:
  /**
   * Generate water.
   */
  void GenerateWater() const;

 private:
  void GenerateNaturalRivers() const;

  void GenerateRiverFromSource(int startX, int startY, int length) const;

  void GenerateLakesInValleys() const;

  bool IsValidForWater(int x, int y) const;

  void SetAdjacentTilesElevationToZero(int x, int y) const;
};
}