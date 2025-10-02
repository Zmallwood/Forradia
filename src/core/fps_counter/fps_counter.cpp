/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "fps_counter.hpp"

namespace forr {
  void fps_counter::update() {
    auto now{get_ticks()};
    if (now > m_ticks_last_update + k_one_second_millis) {
      m_fps = m_frames_count;
      m_frames_count = 0;
      m_ticks_last_update = now;
    }
    ++m_frames_count;
  }
}
