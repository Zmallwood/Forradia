/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateCreatures.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Creature.hpp"

namespace Forradia
{
    void GenerateCreatures()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        auto numRats{200 + RandomInt(15)};

        for (auto i = 0; i < numRats; i++)
        {
            auto x{RandomInt(size.width)};
            auto y{RandomInt(size.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (tile && !tile->GetCreature() && tile->GetGround() != Hash("GroundWater"))
            {
                auto newCreature = std::make_shared<Creature>("CreatureRat");
                tile->SetCreature(newCreature);
                worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }
    }
}