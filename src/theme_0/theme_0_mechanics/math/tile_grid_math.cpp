/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  size_f calculate_tile_size() {
    auto numGridRows{get_singleton<game_properties>().k_numGridRows};
    auto tileHeight{1.0f / numGridRows};
    auto aspectRatio{calculate_aspect_ratio()};
    auto tileWidth{tileHeight / aspectRatio};
    return {tileWidth, tileHeight};
  }

  size calculate_grid_size() {
    auto tileSize{calculate_tile_size()};
    auto numGridColumns{c_int(1.0f / tileSize.width) + 1};
    auto numGridRows{get_singleton<game_properties>().k_numGridRows};
    return {numGridColumns, numGridRows};
  }
}