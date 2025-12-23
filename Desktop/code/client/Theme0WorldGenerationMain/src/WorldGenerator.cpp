/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerator.hpp"
#include "WorldGeneratorEntities.hpp"
#include "WorldGeneratorGround.hpp"
#include "WorldGeneratorObjects.hpp"
#include "WorldGeneratorWater.hpp"

namespace Forradia::Theme0
{
    auto WorldGenerator::GenerateNewWorld() -> void
    {
        WorldGenerator::Prepare();

        WorldGeneratorGround::Instance().GenerateGroundWithElevation();
        WorldGeneratorWater::Instance().GenerateWater();
        WorldGeneratorObjects::Instance().GenerateObjects();
        WorldGeneratorEntities::Instance().GenerateEntities();
    }

    auto WorldGenerator::Prepare() -> void
    {
        WorldGeneratorGround::Instance().Prepare();
        WorldGeneratorWater::Instance().Prepare();
        WorldGeneratorObjects::Instance().Prepare();
        WorldGeneratorEntities::Instance().Prepare();
    }
}
