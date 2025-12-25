/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGenerator.hpp"
    #include "Content/WorldGeneration/Entities/WorldGeneratorEntities.hpp"
    #include "Content/WorldGeneration/Ground/WorldGeneratorGround.hpp"
    #include "Content/WorldGeneration/Objects/WorldGeneratorObjects.hpp"
    #include "Content/WorldGeneration/Water/WorldGeneratorWater.hpp"
// clang-format on

namespace Forradia::Theme0
{
    auto WorldGenerator::generateNewWorld() -> void
    {
        WorldGenerator::prepare();

        WorldGeneratorGround::instance().generateGroundWithElevation();
        WorldGeneratorWater::instance().generateWater();
        WorldGeneratorObjects::instance().generateObjects();
        WorldGeneratorEntities::instance().generateEntities();
    }

    auto WorldGenerator::prepare() -> void
    {
        WorldGeneratorGround::instance().prepare();
        WorldGeneratorWater::instance().prepare();
        WorldGeneratorObjects::instance().prepare();
        WorldGeneratorEntities::instance().prepare();
    }
}
