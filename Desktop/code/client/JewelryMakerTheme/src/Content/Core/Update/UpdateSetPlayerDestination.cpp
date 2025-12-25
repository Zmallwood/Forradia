/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "UpdateSetPlayerDestination.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "TileHovering.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto updateSetPlayerDestination() -> void
    {
        auto newDestination{TileHovering::getHoveredCoordinate()};

        Player::instance().setDestination(newDestination);
    }
}
