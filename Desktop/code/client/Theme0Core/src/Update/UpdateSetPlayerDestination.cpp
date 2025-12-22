/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateSetPlayerDestination.hpp"
#include "Player/Player.hpp"
#include "TileHovering.hpp"

namespace Forradia::Theme0
{
    auto UpdateSetPlayerDestination() -> void
    {
        auto newDestination{TileHovering::Instance().GetHoveredCoordinate()};
        Player::Instance().SetDestination(newDestination);
    }
}
