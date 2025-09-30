/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "TileGridMath.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"

namespace Forradia {
  SizeF CalculateTileSize() {
    auto numGridRows{_<GameProperties>().k_numGridRows};

    auto tileHeight{1.0f / numGridRows};

    auto aspectRatio{CalculateAspectRatio()};

    auto tileWidth{tileHeight / aspectRatio};

    return {tileWidth, tileHeight};
  }

  Size CalculateGridSize() {
    auto tileSize{CalculateTileSize()};

    auto numGridColumns{CInt(1.0f / tileSize.width) + 1};

    auto numGridRows{_<GameProperties>().k_numGridRows};

    return {numGridColumns, numGridRows};
  }
}