/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerator.hpp"
#include "WorldGeneratorEntities.hpp"
#include "WorldGeneratorGround.hpp"
#include "WorldGeneratorObjects.hpp"
#include "WorldGeneratorWater.hpp"
#include "WorldGeneratorLowerFloors.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGenerator::generateNewWorld() -> void
    {
        WorldGenerator::prepare();

        WorldGeneratorGround::generateGroundWithElevation();
        WorldGeneratorWater::generateWater();
        WorldGeneratorObjects::generateObjects();
        WorldGeneratorEntities::generateEntities();
        WorldGeneratorLowerFloors::generateLowerFloors();
    }

    auto WorldGenerator::prepare() -> void
    {
        WorldGeneratorGround::prepare();
        WorldGeneratorWater::prepare();
        WorldGeneratorObjects::prepare();
        WorldGeneratorEntities::prepare();
        WorldGeneratorLowerFloors::prepare();
    }
}
