/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "fps_counter.hpp"

namespace forr {
  void FPSCounter::Update() {
    auto now{GetTicks()};
    if (now > m_ticksLastUpdate + k_oneSecondMillis) {
      m_fps = m_framesCount;
      m_framesCount = 0;
      m_ticksLastUpdate = now;
    }
    ++m_framesCount;
  }
}
