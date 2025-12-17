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
  void Update();

  /**
   * Provides the hovered coordinate.
   */
  auto GetHoveredCoordinate() const {
    return m_hoveredCoordinate;
  }

 private:
  void DetermineHoveredCoordinateWithRaycasting();

  void IterateOverRenderedTiles();

  bool DetermineIfTileIsHovered(int xCoordinate, int yCoordinate) const;

  bool CheckIfRayIntersectsTile(int xCoordinate, int yCoordinate) const;

  Point m_hoveredCoordinate{-1, -1};
};
}