//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "Theme0Properties.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateNewWorld()
    {
        this->Prepare();

        this->ClearWithDirt();

        // New creative generation order:
        // 1. Create elevation and terrain features first
        this->GenerateElevationWithBiomes();
        this->GenerateMountainRanges();
        this->GenerateValleys();

        // 2. Generate ground types based on biomes
        this->GenerateBiomeBasedTerrain();
        this->GenerateGrassBiomes();
        this->GenerateRockFormations();

        // 3. Generate water features in valleys and flowing from mountains
        this->GenerateLakesInValleys();
        this->GenerateNaturalRivers();

        // 4. Generate vegetation in appropriate biomes
        this->GenerateForests();
        this->GenerateMeadows();
        this->GenerateObjectsInBiomes();

        // 5. Generate creatures and robots in ecosystems
        this->GenerateCreaturesInEcosystems();
        this->GenerateRobotsInAreas();
    }

    void WorldGenerator::Prepare()
    {
        m_worldArea = _<Theme0::World>().GetCurrentWorldArea();

        m_size = m_worldArea->GetSize();

        m_scale = _<Theme0::Theme0Properties>().GetWorldScaling();
    }
}