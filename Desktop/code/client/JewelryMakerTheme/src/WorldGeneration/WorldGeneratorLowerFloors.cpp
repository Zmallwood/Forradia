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
    auto WorldGeneratorLowerFloors::generateLowerFloors() -> void
    {
        WorldGeneratorLowerFloors::clearWithDirt();
        WorldGeneratorLowerFloors::fillWithStoneBlocks();
    }

    auto WorldGeneratorLowerFloors::clearWithDirt() -> void
    {
        auto worldArea{getWorldAreaLowerFloors()};
        auto worldAreaSize{getWorldAreaLowerFloorsSize()};

        for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
            {
                auto tile{worldArea->getTile(xPos, yPos)};

                if (!tile)
                {
                    continue;
                }

                tile->setGround("GroundDirt");
            }
        }
    }

    auto WorldGeneratorLowerFloors::fillWithStoneBlocks() -> void
    {
        auto worldArea{getWorldAreaLowerFloors()};
        auto worldAreaSize{getWorldAreaLowerFloorsSize()};

        for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
            {
                auto tile{worldArea->getTile(xPos, yPos)};

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
