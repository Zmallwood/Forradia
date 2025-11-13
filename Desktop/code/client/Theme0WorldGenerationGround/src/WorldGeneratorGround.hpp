//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0
{
    class WorldGeneratorGround : public WorldGeneratorBase
    {
      public:
        void GenerateGroundWithElevation() const;

      private:
        void ClearWithDirt() const;

        void GenerateGrassBiomes() const;

        void GenerateRockFormations() const;

        void GenerateElevationWithBiomes() const;

        void GenerateMountainRanges() const;

        void GenerateValleys() const;
    };
}