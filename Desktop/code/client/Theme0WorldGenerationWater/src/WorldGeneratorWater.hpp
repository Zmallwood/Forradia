//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0 {
    ///
    /// World generator for water.
    ///
    class WorldGeneratorWater : public WorldGeneratorBase {
      public:
        ///
        /// Generate water.
        ///
        void GenerateWater() const;

      private:
        ///
        /// Generate natural rivers.
        ///
        void GenerateNaturalRivers() const;

        ///
        /// Generate a river from a source.
        ///
        /// @param startX The starting X coordinate.
        /// @param startY The starting Y coordinate.
        /// @param length The length of the river.
        ///
        void GenerateRiverFromSource(int startX, int startY, int length) const;

        ///
        /// Generate lakes in valleys.
        ///
        void GenerateLakesInValleys() const;

        ///
        /// Check if a tile is valid for water.
        ///
        /// @param x The X coordinate.
        /// @param y The Y coordinate.
        /// @return True if the tile is valid for water, false otherwise.
        ///
        bool IsValidForWater(int x, int y) const;

        ///
        /// Set the elevation of adjacent tiles to zero.
        ///
        /// @param x The X coordinate.
        /// @param y The Y coordinate.
        ///
        void SetAdjacentTilesElevationToZero(int x, int y) const;
    };
}