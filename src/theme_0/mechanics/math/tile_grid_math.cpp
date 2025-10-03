/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_grid_math.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"

namespace forr {
  size_f calculate_tile_size() {
    auto num_grid_rows{get_ston<game_properties>().k_num_grid_rows};
    auto tl_h{1.0f / num_grid_rows};
    auto asp_rat{calc_aspect_ratio()};
    auto tl_w{tl_h / asp_rat};
    return {tl_w, tl_h};
  }

  size calculate_grid_size() {
    auto tl_sz{calculate_tile_size()};
    auto num_grid_cols{c_int(1.0f / tl_sz.w) + 1};
    auto num_grid_rows{get_ston<game_properties>().k_num_grid_rows};
    return {num_grid_cols, num_grid_rows};
  }
}