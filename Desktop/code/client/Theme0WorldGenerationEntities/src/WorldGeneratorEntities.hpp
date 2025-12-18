/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0 {
/**
 * Generates entities for the world.
 */
class WorldGeneratorEntities : public WorldGeneratorBase {
 public:
  /**
   * Generates entities for the world.
   */
  auto GenerateEntities() const -> void;

 private:
  auto GenerateCreaturesInEcosystems() const -> void;

  auto IsNearWater(int x, int y, int radius) const -> bool;
};
}
