/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  /**
   * Tile data structure for batched rendering.
   */
  class TileData {
   public:
    /**
     * The unique render ID.
     */
    int uniqueRenderID{0};

    /**
     * The image name hash.
     */
    int imageNameHash{0};

    /**
     * The x coordinate.
     */
    int xCoordinate{0};

    /**
     * The y coordinate.
     */
    int yCoordinate{0};

    /**
     * The tile size.
     */
    float tileSize{0.0f};

    /**
     * The elevations.
     */
    Vector<float> elevations;

    /**
     * Whether to force update the tile.
     */
    bool forceUpdate{false};

    /**
     * The 00 color.
     */
    Color color00{Palette::GetColor<Hash("White")>()};

    /**
     * The 10 color.
     */
    Color color10{Palette::GetColor<Hash("White")>()};

    /**
     * The 11 color.
     */
    Color color11{Palette::GetColor<Hash("White")>()};

    /**
     * The 01 color.
     */
    Color color01{Palette::GetColor<Hash("White")>()};
  };
}
