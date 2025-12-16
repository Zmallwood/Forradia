//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0 {
    ///
    /// Determines and provides the tile hovered by the mouse.
    ///
    class TileHovering {
      public:
        ///
        /// Updates the tile hovering.
        ///
        void Update();

        ///
        /// Provides the hovered coordinate.
        ///
        auto GetHoveredCoordinate() const {
            return m_hoveredCoordinate;
        }

      private:
        ///
        /// Determines the hovered coordinate with raycasting.
        ///
        void DetermineHoveredCoordinateWithRaycasting();

        ///
        /// Iterates over the rendered tiles.
        ///
        void IterateOverRenderedTiles();

        ///
        /// Determines if the tile is hovered.
        ///
        bool DetermineIfTileIsHovered(int xCoordinate, int yCoordinate) const;

        ///
        /// Checks if the ray intersects the tile.
        ///
        bool CheckIfRayIntersectsTile(int xCoordinate, int yCoordinate) const;

        Point m_hoveredCoordinate{-1, -1}; ///< The coordinate of the tile hovered by the mouse.
    };
}