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
    void WorldGenerator::GenerateCreatures() const
    {
        // auto numRats{200 * m_scale +
        //              GetRandomInt(15 * m_scale)};

        // for (auto i = 0; i < numRats; i++)
        // {
        //     auto x{GetRandomInt(m_size.width)};

        //     auto y{GetRandomInt(m_size.height)};

        //     auto tile{m_worldArea->GetTile(x, y)};

        //     if (tile && !tile->GetCreature() &&
        //         tile->GetGround() != Hash("GroundWater"))
        //     {
        //         auto newCreature =
        //             std::make_shared<Theme0::Creature>(
        //                 "CreatureRat");

        //         tile->SetCreature(newCreature);

        //         m_worldArea->GetCreaturesMirrorRef().insert(
        //             {tile->GetCreature(), {x, y}});
        //     }
        // }

        auto numWhiteRabbits{200 * m_scale + GetRandomInt(15 * m_scale)};

        for (auto i = 0; i < numWhiteRabbits; i++)
        {
            auto x{GetRandomInt(m_size.width)};

            auto y{GetRandomInt(m_size.height)};

            auto tile{m_worldArea->GetTile(x, y)};

            if (tile && !tile->GetCreature() && tile->GetGround() != Hash("GroundWater"))
            {
                auto newCreature = std::make_shared<Theme0::Creature>("CreatureWhiteRabbit");

                tile->SetCreature(newCreature);

                m_worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }

        // auto numButterflies{200 * m_scale +
        //                     GetRandomInt(15 * m_scale)};

        // for (auto i = 0; i < numButterflies; i++)
        // {
        //     auto x{GetRandomInt(m_size.width)};

        //     auto y{GetRandomInt(m_size.height)};

        //     auto tile{m_worldArea->GetTile(x, y)};

        //     if (tile && !tile->GetCreature() &&
        //         tile->GetGround() != Hash("GroundWater"))
        //     {
        //         auto newCreature =
        //             std::make_shared<Theme0::Creature>(
        //                 "CreatureButterfly");

        //         tile->SetCreature(newCreature);

        //         m_worldArea->GetCreaturesMirrorRef().insert(
        //             {tile->GetCreature(), {x, y}});
        //     }
        // }
    }
}