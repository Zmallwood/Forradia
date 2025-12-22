/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "TileDrawGroup.hpp"
#include <unordered_map>

namespace Forradia {
    /**
     * A rendering operation for a group of tiles.
     */
    class GroundRenderingGroupOperation {
      public:
        std::unordered_map<int, TileDrawGroup> tilesByTexture; ///< The tiles by texture.
    };
}
