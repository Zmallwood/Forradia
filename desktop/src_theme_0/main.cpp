/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"
#include "game_props.hpp"
#include "scripts.hpp"
#include "world_struct.hpp"

int main(int argc, char **argv)
{
    using namespace Forradia;
    _<engine>().init(_<Theme0::game_props>().k_game_win_title,
                     _<Theme0::game_props>().k_clear_color);
    _<script_engine>().init();
    _<script_engine>().load_scripts();
    _<world>().init(_<Theme0::game_props>().k_w_area_sz,
                    _<Theme0::game_props>().k_world_scaling);
    _<engine>().run();
    return 0;
}
