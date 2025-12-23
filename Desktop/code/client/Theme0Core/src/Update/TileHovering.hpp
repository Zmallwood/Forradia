/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/Point.hpp"

namespace Forradia::Theme0
{
    /**
     * Determines and provides the tile hovered by the mouse.
     */
    class TileHovering
    {
      public:
        static auto Instance() -> TileHovering &
        {
            static TileHovering instance;
            return instance;
        }

        // Delete copy/move
        TileHovering(const TileHovering &) = delete;

        auto operator=(const TileHovering &) -> TileHovering & = delete;

        TileHovering() = default;

        /**
         * Updates the tile hovering.
         */
        static auto Update() -> void;

        /**
         * Provides the hovered coordinate.
         */
        [[nodiscard]] static auto GetHoveredCoordinate() -> Point
        {
            return m_hoveredCoordinate;
        }

      private:
        static auto DetermineHoveredCoordinateWithRaycasting() -> void;

        static auto IterateOverRenderedTiles() -> void;

        static auto DetermineIfTileIsHovered(int xCoordinate, int yCoordinate) -> bool;

        static auto CheckIfRayIntersectsTile(int xCoordinate, int yCoordinate) -> bool;

        inline static Point m_hoveredCoordinate{-1, -1};
    };
}
