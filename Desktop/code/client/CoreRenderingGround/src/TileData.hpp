//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Tile data structure for batched rendering.
    ///
    class TileData
    {
      public:
        int uniqueRenderID; ///< The unique render ID.

        int imageNameHash; ///< The image name hash.

        int xCoordinate; ///< The x coordinate.

        int yCoordinate; ///< The y coordinate.

        float tileSize; ///< The tile size.

        Vector<float> elevations; ///< The elevations.

        bool forceUpdate; ///< Whether to force update the tile.
    };
}