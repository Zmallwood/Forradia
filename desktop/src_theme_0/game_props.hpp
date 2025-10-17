/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

_NS_START_
class game_props {
 public:
  static constexpr str k_game_win_title{"Forradia"};
  static constexpr color k_clear_color{colors::black};
  static constexpr int k_num_grid_rows{15};
  static constexpr sz k_w_area_sz{120, 100};
  static constexpr float k_world_scaling{5.0f};
};
_NS_END_