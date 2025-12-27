/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerator.hpp"
#include "WorldGeneration/Entities/WorldGeneratorEntities.hpp"
#include "WorldGeneration/Ground/WorldGeneratorGround.hpp"
#include "WorldGeneration/Objects/WorldGeneratorObjects.hpp"
#include "WorldGeneration/Water/WorldGeneratorWater.hpp"
#include "WorldGeneration/LowerFloors/WorldGeneratorLowerFloors.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGenerator::generateNewWorld() -> void
    {
        WorldGenerator::prepare();

        WorldGeneratorGround::instance().generateGroundWithElevation();
        WorldGeneratorWater::instance().generateWater();
        WorldGeneratorObjects::instance().generateObjects();
        WorldGeneratorEntities::instance().generateEntities();
        WorldGeneratorLowerFloors::instance().generateLowerFloors();
    }

    auto WorldGenerator::prepare() -> void
    {
        WorldGeneratorGround::instance().prepare();
        WorldGeneratorWater::instance().prepare();
        WorldGeneratorObjects::instance().prepare();
        WorldGeneratorEntities::instance().prepare();
        WorldGeneratorLowerFloors::instance().prepare();
    }
}
