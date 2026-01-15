/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "updateSetPlayerDestination.hpp"
#include "Player/Player.hpp"
#include "TileHovering.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto updateSetPlayerDestination() -> void
    {
        auto newDestination{TileHovering::getHoveredCoordinate()};

        Player::instance().setDestination(newDestination);
    }
}
