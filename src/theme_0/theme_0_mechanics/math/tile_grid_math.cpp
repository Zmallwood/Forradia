/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  size_f CalculateTileSize() {
    auto numGridRows{GetSingleton<game_properties>().k_numGridRows};
    auto tileHeight{1.0f / numGridRows};
    auto aspectRatio{CalculateAspectRatio()};
    auto tileWidth{tileHeight / aspectRatio};
    return {tileWidth, tileHeight};
  }

  size CalculateGridSize() {
    auto tileSize{CalculateTileSize()};
    auto numGridColumns{CInt(1.0f / tileSize.width) + 1};
    auto numGridRows{GetSingleton<game_properties>().k_numGridRows};
    return {numGridColumns, numGridRows};
  }
}