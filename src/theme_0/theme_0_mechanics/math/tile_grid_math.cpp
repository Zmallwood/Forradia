/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  size_f calculate_tile_size() {
    auto num_grid_rows{get_singleton<game_properties>().k_num_grid_rows};
    auto tile_height{1.0f / num_grid_rows};
    auto aspect_ratio{calculate_aspect_ratio()};
    auto tile_width{tile_height / aspect_ratio};
    return {tile_width, tile_height};
  }

  size calculate_grid_size() {
    auto tile_size{calculate_tile_size()};
    auto num_grid_columns{c_int(1.0f / tile_size.w) + 1};
    auto num_grid_rows{get_singleton<game_properties>().k_num_grid_rows};
    return {num_grid_columns, num_grid_rows};
  }
}