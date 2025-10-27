//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "NPC.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateNPCs() const
    {
        auto numNPC0s{200 * m_scale +
                      GetRandomInt(15 * m_scale)};

        for (auto i = 0; i < numNPC0s; i++)
        {
            auto x{GetRandomInt(m_size.width)};

            auto y{GetRandomInt(m_size.height)};

            auto tile{m_worldArea->GetTile(x, y)};

            if (tile && !tile->GetNPC() &&
                tile->GetGround() != Hash("GroundWater"))
            {
                auto newNPC =
                    std::make_shared<Theme0::NPC>("npc0");

                tile->SetNPC(newNPC);

                m_worldArea->GetNPCsMirrorRef().insert(
                    {tile->GetNPC(), {x, y}});
            }
        }
    }
}