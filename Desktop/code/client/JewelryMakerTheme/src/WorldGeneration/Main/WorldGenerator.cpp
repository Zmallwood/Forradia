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
