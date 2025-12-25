/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "PlayerObjectsInventory.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto PlayerObjectsInventory::initialize() -> void
    {
        // Add starting objects.
        addObject("ObjectRedApple");
        addObject("ObjectRedApple");
        addObject("ObjectPlasticAxe");
        addObject("ObjectChisel");
        addObject("ObjectHammer");
    }
}
