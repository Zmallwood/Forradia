/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
/**
 * Determines and provides the tile hovered by the mouse.
 */
class TileHovering {
 public:
  /**
   * Updates the tile hovering.
   */
  auto Update() -> void;

  /**
   * Provides the hovered coordinate.
   */
  auto GetHoveredCoordinate() const {
    return m_hoveredCoordinate;
  }

 private:
  auto DetermineHoveredCoordinateWithRaycasting() -> void;

  auto IterateOverRenderedTiles() -> void;

  auto DetermineIfTileIsHovered(int xCoordinate, int yCoordinate) const -> bool;

  auto CheckIfRayIntersectsTile(int xCoordinate, int yCoordinate) const -> bool;

  Point m_hoveredCoordinate{-1, -1};
};
}
