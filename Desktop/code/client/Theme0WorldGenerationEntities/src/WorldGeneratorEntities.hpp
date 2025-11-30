//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "WorldGeneratorBase.hpp"

namespace AAK
{
    namespace Forradia::Theme0
    {
        ///
        /// Generates entities for the world.
        ///
        class WorldGeneratorEntities : public WorldGeneratorBase
        {
          public:
            ///
            /// Generates entities for the world.
            ///
            void GenerateEntities() const;

          private:
            ///
            /// Generates creatures in ecosystems.
            ///
            void GenerateCreaturesInEcosystems() const;

            ///
            /// Generates robots in areas.
            ///
            void GenerateRobotsInAreas() const;

            ///
            /// Checks if a point is near water.
            ///
            /// @param x The x coordinate of the point.
            /// @param y The y coordinate of the point.
            /// @param radius The radius to check.
            /// @return True if the point is near water, false otherwise.
            ///
            bool IsNearWater(int x, int y, int radius) const;
        };
    }
}