//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0
{
    class WorldGeneratorObjects : public WorldGeneratorBase
    {
      public:
        void GenerateObjects() const;

      private:
        void GenerateForests() const;

        void GenerateMeadows() const;

        void GenerateObjectsInBiomes() const;
    };
}