/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0 {
///
/// The world generator for objects.
///
class WorldGeneratorObjects : public WorldGeneratorBase {
 public:
  ///
  /// Generate the objects in the world.
  ///
  void GenerateObjects() const;

 private:
  ///
  /// Generate the forests in the world.
  ///
  void GenerateForests() const;

  ///
  /// Generate the meadows in the world.
  ///
  void GenerateMeadows() const;

  ///
  /// Generate the objects in the biomes.
  ///
  void GenerateObjectsInBiomes() const;

  ///
  /// Check if the tile is valid for flora.
  ///
  /// @param x The x coordinate of the tile.
  /// @param y The y coordinate of the tile.
  /// @return True if the tile is valid for flora, false otherwise.
  ///
  bool IsValidForFlora(int x, int y) const;
};
}