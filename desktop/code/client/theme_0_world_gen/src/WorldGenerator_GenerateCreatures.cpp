//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "Creature.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateCreaturesInEcosystems() const
    {
        // Generate white rabbits - prefer areas near water and in meadows/grass
        auto numWhiteRabbits{180 * m_scale + GetRandomInt(40 * m_scale)};

        for (auto i = 0; i < numWhiteRabbits; i++)
        {
            auto x{GetRandomInt(m_size.width)};
            auto y{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(x, y);
            if (!tile || tile->GetCreature() || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Rabbits prefer grass areas, especially near water
            auto prefersLocation = false;

            if (tile->GetGround() == Hash("GroundGrass"))
            {
                // Higher chance if near water
                if (IsNearWater(x, y, 8))
                {
                    prefersLocation = GetRandomInt(100) < 40;
                }
                else
                {
                    prefersLocation = GetRandomInt(100) < 20;
                }
            }
            else if (tile->GetGround() == Hash("GroundDirt"))
            {
                // Lower chance on dirt
                prefersLocation = GetRandomInt(100) < 5;
            }

            if (prefersLocation)
            {
                auto newCreature = std::make_shared<Theme0::Creature>("CreatureWhiteRabbit");

                tile->SetCreature(newCreature);

                m_worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }

        // Create creature clusters near water sources (more realistic ecosystems)
        auto numWaterSources{15 + GetRandomInt(10)};

        for (auto source = 0; source < numWaterSources; source++)
        {
            auto attempts = 0;
            int waterX = 0;
            int waterY = 0;
            bool foundWater = false;

            // Find a water tile
            while (attempts < 30 && !foundWater)
            {
                waterX = GetRandomInt(m_size.width);
                waterY = GetRandomInt(m_size.height);

                auto tile = m_worldArea->GetTile(waterX, waterY);
                if (tile && tile->GetGround() == Hash("GroundWater"))
                {
                    foundWater = true;
                }
                attempts++;
            }

            if (!foundWater)
            {
                continue;
            }

            // Create a small ecosystem around the water source
            auto ecosystemRadius{5 + GetRandomInt(8)};
            auto creaturesInEcosystem{3 + GetRandomInt(5)};

            for (auto c = 0; c < creaturesInEcosystem; c++)
            {
                auto angle = GetRandomInt(360) * M_PI / 180.0f;
                auto distance = 2 + GetRandomInt(ecosystemRadius);
                auto creatureX = waterX + CInt(std::cos(angle) * distance);
                auto creatureY = waterY + CInt(std::sin(angle) * distance);

                if (!m_worldArea->IsValidCoordinate(creatureX, creatureY))
                {
                    continue;
                }

                auto creatureTile = m_worldArea->GetTile(creatureX, creatureY);
                if (!creatureTile || creatureTile->GetCreature() ||
                    creatureTile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                // Prefer grass for the ecosystem
                if (creatureTile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 60)
                {
                    auto newCreature = std::make_shared<Theme0::Creature>("CreatureWhiteRabbit");

                    creatureTile->SetCreature(newCreature);

                    m_worldArea->GetCreaturesMirrorRef().insert(
                        {creatureTile->GetCreature(), {creatureX, creatureY}});
                }
            }
        }
    }
}
