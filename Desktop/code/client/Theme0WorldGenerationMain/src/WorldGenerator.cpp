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
    void WorldGenerator::GenerateNewWorld()
    {
        this->Prepare();

        _<WorldGeneratorGround>().ClearWithDirt();

        _<WorldGeneratorGround>().GenerateElevationWithBiomes();
        _<WorldGeneratorGround>().GenerateMountainRanges();
        _<WorldGeneratorGround>().GenerateValleys();

        // 2. Generate ground types based on biomes
        _<WorldGeneratorGround>().GenerateBiomeBasedTerrain();
        _<WorldGeneratorGround>().GenerateGrassBiomes();
        _<WorldGeneratorGround>().GenerateRockFormations();

        // 3. Generate water features in valleys and flowing from mountains
        _<WorldGeneratorWater>().GenerateLakesInValleys();
        _<WorldGeneratorWater>().GenerateNaturalRivers();

        // // 3.5. Enforce minimum elevation for non-water tiles
        _<WorldGeneratorGround>().EnforceMinimumElevationForNonWaterTiles();

        // // 4. Generate vegetation in appropriate biomes
        _<WorldGeneratorObjects>().GenerateForests();
        _<WorldGeneratorObjects>().GenerateMeadows();
        _<WorldGeneratorObjects>().GenerateObjectsInBiomes();

        // // 5. Generate creatures and robots in ecosystems
        _<WorldGeneratorEntities>().GenerateCreaturesInEcosystems();
        _<WorldGeneratorEntities>().GenerateRobotsInAreas();
    }

    void WorldGenerator::Prepare()
    {
        _<WorldGeneratorGround>().Prepare();

        _<WorldGeneratorWater>().Prepare();

        _<WorldGeneratorObjects>().Prepare();

        _<WorldGeneratorEntities>().Prepare();
    }
}