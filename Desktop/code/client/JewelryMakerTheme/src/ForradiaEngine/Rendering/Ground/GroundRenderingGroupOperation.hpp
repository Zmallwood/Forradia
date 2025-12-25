/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "TileDrawGroup.hpp"
    #include <unordered_map>
// clang-format on

namespace Forradia
{
    /**
     *   A rendering operation for a group of tiles.
     */
    class GroundRenderingGroupOperation
    {
      public:
        std::unordered_map<int, TileDrawGroup> tilesByTexture{}; ///< The tiles by texture.
    };
}
