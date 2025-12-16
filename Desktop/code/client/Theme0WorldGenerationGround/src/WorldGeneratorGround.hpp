/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0 {
///
/// The world generator for the ground with elevation.
///
class WorldGeneratorGround : public WorldGeneratorBase {
 public:
  ///
  /// Do all the steps to generate the ground with elevation.
  ///
  void GenerateGroundWithElevation() const;

 private:
  ///
  /// Clear the ground with dirt and set the elevation to the default ground elevation.
  ///
  void ClearWithDirt() const;

  ///
  /// Generate the grass biomes.
  ///
  void GenerateGrassBiomes() const;

  ///
  /// Generate the rock formations.
  ///
  void GenerateRockFormations() const;

  ///
  /// Generate the elevation with biomes.
  ///
  void GenerateElevationWithBiomes() const;

  ///
  /// Generate the mountain ranges.
  ///
  void GenerateMountainRanges() const;

  ///
  /// Generate the valleys.
  ///
  void GenerateValleys() const;

  ///
  /// Create a biome cluster.
  ///
  /// @param centerX The x coordinate of the center of the cluster.
  /// @param centerY The y coordinate of the center of the cluster.
  /// @param radius The radius of the cluster.
  /// @param groundType The ground type of the cluster.
  ///
  void CreateBiomeCluster(int centerX, int centerY, int radius, StringView groundType) const;

  ///
  /// Get the maximum elevation.
  ///
  /// @return The maximum elevation.
  ///
  int GetMaxElevation() const;

  ///
  /// Get the maximum slope per tile.
  ///
  /// @return The maximum slope per tile.
  ///
  int GetMaxSlopePerTile() const;

  ///
  /// Get the maximum allowed elevation.
  ///
  /// @param x The x coordinate of the tile.
  /// @param y The y coordinate of the tile.
  /// @param currentElevation The current elevation of the tile.
  /// @return The maximum allowed elevation.
  ///
  int GetMaxAllowedElevation(int x, int y, int currentElevation) const;

  ///
  /// Clamp the elevation.
  ///
  /// @param elevation The elevation to clamp.
  /// @return The clamped elevation.
  ///
  int ClampElevation(int elevation) const;

  ///
  /// Create an elevation hill.
  ///
  /// @param centerX The x coordinate of the center of the hill.
  /// @param centerY The y coordinate of the center of the hill.
  /// @param radius The radius of the hill.
  /// @param maxElevation The maximum elevation of the hill.
  ///
  void CreateElevationHill(int centerX, int centerY, int radius, int maxElevation) const;
};
}