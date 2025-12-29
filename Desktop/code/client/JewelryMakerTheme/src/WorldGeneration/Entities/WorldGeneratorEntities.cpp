/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorEntities.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorEntities::generateEntities() -> void
    {
        generateEntitiesInEcosystems();
    }
}
