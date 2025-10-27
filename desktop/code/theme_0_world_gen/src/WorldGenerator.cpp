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

        this->GenerateGrass();

        this->GenerateLakes();

        this->GenerateElevation();

        this->GenerateRock();

        this->GenerateRivers();

        this->GenerateObjects();

        this->GenerateCreatures();

        this->GenerateNPCs();
    }

    void WorldGenerator::Prepare()
    {
        m_worldArea =
            _<Theme0::World>().GetCurrentWorldArea();

        m_size = m_worldArea->GetSize();

        m_scale =
            _<Theme0::Theme0Properties>().k_worldScaling;
    }
}