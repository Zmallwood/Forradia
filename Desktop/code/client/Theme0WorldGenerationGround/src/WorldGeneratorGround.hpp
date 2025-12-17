/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0 {
/**
 * The world generator for the ground with elevation.
 */
class WorldGeneratorGround : public WorldGeneratorBase {
 public:
  /**
   * Do all the steps to generate the ground with elevation.
   */
  void GenerateGroundWithElevation() const;

 private:
  void ClearWithDirt() const;

  void GenerateGrassBiomes() const;

  void GenerateRockFormations() const;

  void GenerateElevationWithBiomes() const;

  void GenerateMountainRanges() const;

  void GenerateValleys() const;

  void CreateBiomeCluster(int centerX, int centerY, int radius, StringView groundType) const;

  int GetMaxElevation() const;

  int GetMaxSlopePerTile() const;

  int GetMaxAllowedElevation(int x, int y, int currentElevation) const;

  int ClampElevation(int elevation) const;

  void CreateElevationHill(int centerX, int centerY, int radius, int maxElevation) const;
};
}