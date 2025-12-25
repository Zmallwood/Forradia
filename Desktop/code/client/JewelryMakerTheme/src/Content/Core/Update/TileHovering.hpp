/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Geometry/Point.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Determines and provides the tile hovered by the mouse.
     */
    class TileHovering
    {
      public:
        static auto instance() -> TileHovering &
        {
            static TileHovering instance;
            return instance;
        }

        TileHovering(const TileHovering &) = delete;

        auto operator=(const TileHovering &) -> TileHovering & = delete;

        TileHovering() = default;

        /**
         *  Updates the tile hovering.
         */
        static auto update() -> void;

        /**
         *  Provides the hovered coordinate.
         */
        [[nodiscard]] static auto getHoveredCoordinate() -> Point
        {
            return m_hoveredCoordinate;
        }

      private:
        static auto determineHoveredCoordinateWithRayCasting() -> void;

        static auto iterateOverRenderedTiles() -> void;

        static auto determineIfTileIsHovered(int xCoordinate, int yCoordinate) -> bool;

        static auto checkIfRayIntersectsTile(int xCoordinate, int yCoordinate) -> bool;

        inline static Point m_hoveredCoordinate{-1, -1};
    };
}
