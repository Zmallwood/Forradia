/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class game_properties {
  public:
    static constexpr str k_game_window_title{"Forradia"};
    static constexpr color k_clear_color{colors::black};
    static constexpr int k_num_grid_rows{15};
    static constexpr size k_world_area_size{120, 100};
    static constexpr float k_world_scaling_factor{5.0f};
  };
}