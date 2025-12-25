/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGeneratorEntities.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
// clang-format on

namespace Forradia::Theme0
{
    auto WorldGeneratorEntities::generateEntities() const -> void
    {
        generateEntitiesInEcosystems();
    }

    auto WorldGeneratorEntities::isNearWater(int x, int y, int radius) const -> bool
    {
        for (auto checkY = y - radius; checkY <= y + radius; checkY++)
        {
            for (auto checkX = x - radius; checkX <= x + radius; checkX++)
            {
                if (!getWorldArea()->isValidCoordinate(checkX, checkY))
                {
                    continue;
                }

                auto tile{getWorldArea()->getTile(checkX, checkY)};

                if (tile && tile->getGround() == hash("GroundWater"))
                {
                    auto distance{getDistance(x, y, checkX, checkY)};

                    if (distance <= radius)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}
