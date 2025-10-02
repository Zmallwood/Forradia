/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class body_part {
   public:
    auto get_strength() const { return m_strength; }
    auto get_current_energy() const { return m_current_energy; }
    auto get_max_energy() const { return m_max_energy; }
    auto get_temperature() const { return m_temperature; }

   private:
    float m_strength{0.1f};
    float m_current_energy{1.0f};
    float m_max_energy{1.0f};
    float m_temperature{37.0f};
  };
}