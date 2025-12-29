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
        auto generateGroundWithElevation() const -> void;

      private:
        auto clearWithDirt() const -> void;

        auto generateGrassBiomes() const -> void;

        auto generateRockFormations() const -> void;

        auto generateElevationWithBiomes() const -> void;

        auto generateMountainRanges() const -> void;

        auto generateValleys() const -> void;

        auto createBiomeCluster(int centerX, int centerY, int radius,
                                std::string_view groundType) const -> void;

        static auto getMaxElevation() -> int;

        static auto getMaxSlopePerTile() -> int;

        [[nodiscard]] auto getMaxAllowedElevation(int xPos, int yPos, int currentElevation) const
            -> int;

        static auto clampElevation(int elevation) -> int;

        auto createElevationHill(int centerX, int centerY, int radius, int maxElevation) const
            -> void;

        [[nodiscard]] auto setTileElevationForHill(const std::shared_ptr<Tile> &tile, int xPos,
                                                   int yPos, int distance, int radius) const
            -> bool;
    };
}
