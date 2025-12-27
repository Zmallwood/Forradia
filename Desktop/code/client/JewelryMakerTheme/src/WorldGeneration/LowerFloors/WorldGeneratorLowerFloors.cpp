/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorLowerFloors.hpp"

#include "WorldStructure/Tile.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "WorldStructure/ObjectsStack.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorLowerFloors::generateLowerFloors() const -> void
    {
        this->clearWithDirt();
        this->fillWithStoneBlocks();
    }

    auto WorldGeneratorLowerFloors::clearWithDirt() const -> void
    {
        auto worldArea{getWorldAreaLowerFloors()};
        auto worldAreaSize{getWorldAreaLowerFloorsSize()};

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile{worldArea->getTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                tile->setGround("GroundDirt");
            }
        }
    }

    auto WorldGeneratorLowerFloors::fillWithStoneBlocks() const -> void
    {
        auto worldArea{getWorldAreaLowerFloors()};
        auto worldAreaSize{getWorldAreaLowerFloorsSize()};

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile{worldArea->getTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                auto objectsStack{tile->getObjectsStack()};

                objectsStack->addObject("ObjectStoneBlock");
            }
        }
    }
}
