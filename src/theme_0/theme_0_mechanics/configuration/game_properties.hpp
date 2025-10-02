/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class game_properties {
  public:
    static constexpr str k_gameWindowTitle{"Forradia"};
    static constexpr color k_clearColor{colors::black};
    static constexpr int k_numGridRows{15};
    static constexpr size k_worldAreaSize{120, 100};
    static constexpr float k_worldScalingFactor{5.0f};
  };
}