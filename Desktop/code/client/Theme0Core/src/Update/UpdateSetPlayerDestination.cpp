/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateSetPlayerDestination.hpp"
#include "Player/Player.hpp"
#include "TileHovering.hpp"

namespace Forradia {
    auto UpdateSetPlayerDestination() -> void {
        auto newDestination{Singleton<Theme0::TileHovering>().GetHoveredCoordinate()};
        Singleton<Theme0::Player>().SetDestination(newDestination);
    }
}
