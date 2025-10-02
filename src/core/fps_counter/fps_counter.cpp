/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "fps_counter.hpp"

namespace forr {
  void fps_counter::update() {
    auto now{get_ticks()};
    if (now > m_ticksLastUpdate + k_one_second_millis) {
      m_fps = m_framesCount;
      m_framesCount = 0;
      m_ticksLastUpdate = now;
    }
    ++m_framesCount;
  }
}
