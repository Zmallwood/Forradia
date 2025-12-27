/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGeneratorLowerFloors.hpp"

    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
    #include "Content/WorldStructure/ObjectsStack.hpp"
// clang-format on

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
