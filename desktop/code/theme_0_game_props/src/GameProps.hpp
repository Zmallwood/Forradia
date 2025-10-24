/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

#include "Common.hpp"

namespace Forradia
{
#define _HIDE_FROM_OUTLINER_GAME_PROPS_TOP_                                    \
    namespace Theme0                                                           \
    {
    _HIDE_FROM_OUTLINER_GAME_PROPS_TOP_
    namespace Configuration
    {
        class GameProperties
        {
          public:
            static constexpr String k_gameWindowTitle{"Forradia"};
            static constexpr Color k_clearColor{Colors::Black};
            static constexpr int k_numGridRows{15};
            static constexpr Size k_worldAreaSize{120, 100};
            static constexpr float k_worldScaling{5.0f};
        };
    }
    using namespace Configuration;
#define _HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_ }
    _HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_
}