/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_grid_math.hpp"
#include "engine.hpp"
#include "theme_0/func/game_props.hpp"

namespace forr {
  sz_f calc_tl_sz() {
    auto num_grid_rows{_<game_props>().k_num_grid_rows};
    auto tl_h{1.0f / num_grid_rows};
    auto asp_rat{calc_aspect_ratio(_<sdl_device>().get_win())};
    auto tl_w{tl_h / asp_rat};
    return {tl_w, tl_h};
  }

  sz calc_grid_sz() {
    auto tl_sz{calc_tl_sz()};
    auto num_grid_cols{c_int(1.0f / tl_sz.w) + 1};
    auto num_grid_rows{_<game_props>().k_num_grid_rows};
    return {num_grid_cols, num_grid_rows};
  }
}