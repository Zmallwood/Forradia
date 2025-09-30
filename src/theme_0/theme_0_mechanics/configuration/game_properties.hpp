/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  class GameProperties {
  public:
    static constexpr String k_gameWindowTitle{"Forradia"};
    static constexpr Color k_clearColor{Colors::Black};
    static constexpr int k_numGridRows{15};
    static constexpr Size k_worldAreaSize{120, 100};
    static constexpr float k_worldScalingFactor{5.0f};
  };
}