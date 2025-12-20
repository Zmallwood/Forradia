/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

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
        auto GenerateWater() const -> void;

      private:
        auto GenerateNaturalRivers() const -> void;

        auto GenerateRiverFromSource(int startX, int startY, int length) const -> void;

        auto GenerateLakesInValleys() const -> void;

        auto IsValidForWater(int x, int y) const -> bool;

        auto SetAdjacentTilesElevationToZero(int x, int y) const -> void;
    };
}
