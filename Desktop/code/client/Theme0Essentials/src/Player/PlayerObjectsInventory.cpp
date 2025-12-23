/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "PlayerObjectsInventory.hpp"

namespace Forradia::Theme0
{
    auto PlayerObjectsInventory::initialize() -> void
    {
        // Add starting objects.
        addObject("ObjectRedApple");
        addObject("ObjectRedApple");
        addObject("ObjectPlasticAxe");
        addObject("ObjectChisel");
        addObject("ObjectHammer");
        addObject("ObjectDragonEgg");
        addObject("ObjectDragonEgg");
    }
}
