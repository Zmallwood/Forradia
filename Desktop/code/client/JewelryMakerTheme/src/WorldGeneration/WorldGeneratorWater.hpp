/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  World generator for water.
     */
    class WorldGeneratorWater : public WorldGeneratorBase
    {
      public:
        /**
         *  Generate water.
         */
        static auto generateWater() -> void;

      private:
        static auto generateNaturalRivers() -> void;

        static auto generateRiverFromSource(int startX, int startY, int length) -> void;

        static auto generateLakesInValleys() -> void;

        static auto isValidForWater(int x, int y) -> bool;

        static auto setAdjacentTilesElevationToZero(int x, int y) -> void;
    };
}
