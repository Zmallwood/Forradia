/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneration/Common/WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class Tile;

    /**
     *  The world generator for the ground with elevation.
     */
    class WorldGeneratorGround : public WorldGeneratorBase
    {
      public:
        static auto instance() -> WorldGeneratorGround &
        {
            static WorldGeneratorGround instance;
            return instance;
        }

        WorldGeneratorGround(const WorldGeneratorGround &) = delete;

        auto operator=(const WorldGeneratorGround &) -> WorldGeneratorGround & = delete;

        WorldGeneratorGround() = default;

        /**
         *  Do all the steps to generate the ground with elevation.
         */
        static auto generateGroundWithElevation() -> void;

      private:
        static auto clearWithDirt() -> void;

        static auto generateGrassBiomes() -> void;

        static auto generateRockFormations() -> void;

        static auto generateElevationWithBiomes() -> void;

        static auto generateMountainRanges() -> void;

        static auto generateValleys() -> void;

        static auto createBiomeCluster(int centerX, int centerY, int radius,
                                       std::string_view groundType) -> void;

        static auto getMaxElevation() -> int;

        static auto getMaxSlopePerTile() -> int;

        [[nodiscard]] static auto getMaxAllowedElevation(int xPos, int yPos, int currentElevation)
            -> int;

        static auto clampElevation(int elevation) -> int;

        static auto createElevationHill(int centerX, int centerY, int radius, int maxElevation)
            -> void;

        [[nodiscard]] static auto setTileElevationForHill(const std::shared_ptr<Tile> &tile,
                                                          int xPos, int yPos, int distance,
                                                          int radius) -> bool;

        [[nodiscard]] static auto setTileGroundToRock(const std::shared_ptr<Tile> &tile, int xPos,
                                                      int yPos) -> bool;
    };
}
