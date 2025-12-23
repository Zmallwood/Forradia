/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0
{
    /**
        The world generator for the ground with elevation.
     */
    class WorldGeneratorGround : public WorldGeneratorBase
    {
      public:
        static WorldGeneratorGround &Instance()
        {
            static WorldGeneratorGround instance;
            return instance;
        }

        // Delete copy/move
        WorldGeneratorGround(const WorldGeneratorGround &) = delete;

        WorldGeneratorGround &operator=(const WorldGeneratorGround &) = delete;

        WorldGeneratorGround() = default;

        /**
            Do all the steps to generate the ground with elevation.
         */
        auto GenerateGroundWithElevation() const -> void;

      private:
        auto ClearWithDirt() const -> void;

        auto GenerateGrassBiomes() const -> void;

        auto GenerateRockFormations() const -> void;

        auto GenerateElevationWithBiomes() const -> void;

        auto GenerateMountainRanges() const -> void;

        auto GenerateValleys() const -> void;

        auto CreateBiomeCluster(int centerX, int centerY, int radius,
                                std::string_view groundType) const -> void;

        static auto GetMaxElevation() -> int;

        static auto GetMaxSlopePerTile() -> int;

        [[nodiscard]] auto GetMaxAllowedElevation(int x, int y, int currentElevation) const -> int;

        static auto ClampElevation(int elevation) -> int;

        auto CreateElevationHill(int centerX, int centerY, int radius, int maxElevation) const
            -> void;
    };
}
