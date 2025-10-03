/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class body_part {
   public:
    auto get_strength() const { return m_str; }
    auto get_current_energy() const { return m_curr_energy; }
    auto get_max_energy() const { return m_max_energy; }
    auto get_temperature() const { return m_temp; }

   private:
    float m_str{0.1f};
    float m_curr_energy{1.0f};
    float m_max_energy{1.0f};
    float m_temp{37.0f};
  };
}