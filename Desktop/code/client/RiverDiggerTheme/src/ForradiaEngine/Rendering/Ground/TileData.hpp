/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/Common/Matter/Coloring/Palette.hpp"
#include "ForradiaEngine/Common/General/Hash.hpp"
#include <vector>

namespace Forradia
{
    /**
     *  Tile data structure for batched rendering.
     */
    class TileData
    {
      public:
        int uniqueRenderID{0};                             ///< The unique render ID.
        int imageNameHash{0};                              ///< The image name hash.
        int xCoordinate{0};                                ///< The x coordiate.
        int yCoordinate{0};                                ///< The y coordinate.
        float tileSize{0.0F};                              ///< The tile size.
        std::vector<float> elevations{};                   ///< The elevations.
        bool forceUpdate{false};                           ///< Whether to force update the tile.
        Color color00{Palette::getColor<hash("White")>()}; ///< The 00 color.
        Color color10{Palette::getColor<hash("White")>()}; ///< The 10 color.
        Color color11{Palette::getColor<hash("White")>()}; ///< The 11 color.
        Color color01{Palette::getColor<hash("White")>()}; ///< The 01 color.
    };
}
