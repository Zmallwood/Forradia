//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldGeneratorGround.hpp"

#include "WorldGeneratorWater.hpp"

#include "WorldGeneratorObjects.hpp"

#include "WorldGeneratorEntities.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateNewWorld() const
    {
        // Prepare the world generator for generating a new world.

        this->Prepare();

        // Ground.

        _<WorldGeneratorGround>().GenerateGroundWithElevation();

        // Water.

        _<WorldGeneratorWater>().GenerateWater();

        // Objects.

        _<WorldGeneratorObjects>().GenerateObjects();

        // Entities.

        _<WorldGeneratorEntities>().GenerateEntities();
    }

    void WorldGenerator::Prepare() const
    {
        // Prepare all the generators for generating a new world.

        _<WorldGeneratorGround>().Prepare();

        _<WorldGeneratorWater>().Prepare();

        _<WorldGeneratorObjects>().Prepare();

        _<WorldGeneratorEntities>().Prepare();
    }
}