/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GAME_PROPS_TOP_                                    \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GAME_PROPS_TOP_
namespace Configuration
{
    class GameProperties
    {
      public:
        static constexpr String k_game_win_title{"Forradia"};
        static constexpr Color k_clear_color{Colors::black};
        static constexpr int k_num_grid_rows{15};
        static constexpr Size k_w_area_sz{120, 100};
        static constexpr float k_world_scaling{5.0f};
    };
}
using namespace Configuration;
#define _HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_ }
_HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_
_NS_END_