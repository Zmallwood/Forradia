//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0
{
    class WorldGeneratorEntities : public WorldGeneratorBase
    {
      public:
        void GenerateEntities() const;

      private:
        void GenerateCreaturesInEcosystems() const;

        void GenerateRobotsInAreas() const;
    };
}