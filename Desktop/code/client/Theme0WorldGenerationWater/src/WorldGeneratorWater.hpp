//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0
{
    class WorldGeneratorWater : public WorldGeneratorBase
    {
      public:
        void GenerateWater() const;

      private:
        void GenerateNaturalRivers() const;

        void GenerateRiverFromSource(int startX, int startY, int length) const;

        void GenerateLakesInValleys() const;
    };
}