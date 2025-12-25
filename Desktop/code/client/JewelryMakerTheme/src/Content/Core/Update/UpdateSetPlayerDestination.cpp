/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "UpdateSetPlayerDestination.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "TileHovering.hpp"
// clang-format on

namespace Forradia::Theme0
{
    auto updateSetPlayerDestination() -> void
    {
        auto newDestination{TileHovering::getHoveredCoordinate()};

        Player::instance().setDestination(newDestination);
    }
}
