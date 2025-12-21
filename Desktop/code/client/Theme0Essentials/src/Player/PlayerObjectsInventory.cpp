/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "PlayerObjectsInventory.hpp"

namespace Forradia::Theme0 {
    auto PlayerObjectsInventory::Initialize() -> void {
        // Add starting objects.
        AddObject("ObjectRedApple");
        AddObject("ObjectRedApple");
        AddObject("ObjectPlasticAxe");
        AddObject("ObjectChisel");
        AddObject("ObjectHammer");
    }
}
