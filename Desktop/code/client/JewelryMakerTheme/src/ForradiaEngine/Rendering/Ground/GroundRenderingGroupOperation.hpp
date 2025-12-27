/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <unordered_map>
    
    #include "TileDrawGroup.hpp"
// clang-format on

namespace ForradiaEngine
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
