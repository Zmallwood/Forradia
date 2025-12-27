/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Content/WorldGeneration/Common/WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  World generator for water.
     */
    class WorldGeneratorWater : public WorldGeneratorBase
    {
      public:
        static WorldGeneratorWater &instance()
        {
            static WorldGeneratorWater instance;
            return instance;
        }

        WorldGeneratorWater(const WorldGeneratorWater &) = delete;

        WorldGeneratorWater &operator=(const WorldGeneratorWater &) = delete;

        WorldGeneratorWater() = default;

        /**
         *  Generate water.
         */
        auto generateWater() const -> void;

      private:
        auto generateNaturalRivers() const -> void;

        auto generateRiverFromSource(int startX, int startY, int length) const -> void;

        auto generateLakesInValleys() const -> void;

        auto isValidForWater(int x, int y) const -> bool;

        auto setAdjacentTilesElevationToZero(int x, int y) const -> void;
    };
}
