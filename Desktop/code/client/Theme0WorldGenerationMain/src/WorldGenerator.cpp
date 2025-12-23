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
