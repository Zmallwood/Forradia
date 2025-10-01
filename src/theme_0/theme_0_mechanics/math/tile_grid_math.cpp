/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  SizeF CalculateTileSize() {
    auto numGridRows{GetSingleton<GameProperties>().k_numGridRows};
    auto tileHeight{1.0f / numGridRows};
    auto aspectRatio{CalculateAspectRatio()};
    auto tileWidth{tileHeight / aspectRatio};
    return {tileWidth, tileHeight};
  }

  Size CalculateGridSize() {
    auto tileSize{CalculateTileSize()};
    auto numGridColumns{CInt(1.0f / tileSize.width) + 1};
    auto numGridRows{GetSingleton<GameProperties>().k_numGridRows};
    return {numGridColumns, numGridRows};
  }
}