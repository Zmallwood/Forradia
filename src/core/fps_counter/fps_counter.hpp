/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class fps_counter {
  public:
    void update();

    auto get_fps() const { return m_fps; }

  private:
    int m_fps{0};
    int m_frames_count{0};
    int m_ticks_last_update{0};
    const point_f k_position{0.93f, 0.02f};
  };
}