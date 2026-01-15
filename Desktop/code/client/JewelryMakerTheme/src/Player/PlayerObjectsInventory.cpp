/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "PlayerObjectsInventory.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto PlayerObjectsInventory::initialize() -> void
    {
        // Add starting objects.
        addObject("ObjectRedApple");
        addObject("ObjectRedApple");
        addObject("ObjectChisel");
        addObject("ObjectHammer");
        addObject("ObjectShovel");
    }
}
