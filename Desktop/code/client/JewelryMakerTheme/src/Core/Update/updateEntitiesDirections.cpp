/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "updateEntitiesDirections.hpp"
#include "WorldStructure/Entity.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto updateEntitiesDirections() -> void
    {
        auto worldArea{World::instance().getWorldArea(Player::instance().getWorldAreaCoordinate())};
        auto &entities{worldArea->getEntitiesMirrorRef()};

        for (auto entry = entities.begin(); entry != entities.end();)
        {
            auto &entity{entry->first};

            entity->update();

            ++entry;
        }
    }
}