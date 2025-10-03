/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class creature {
   public:
    creature(str_view type_name) : m_type{hash(type_name)} { init(); }

    auto get_type() const { return m_type; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int value) { m_ticks_last_move = value; }

    auto get_movem_spd() const { return m_movem_spd; }

    auto get_dest() const { return m_dest; }

    void set_dest(point val) { m_dest = val; }

   private:
    void init();

    int m_type{0};
    int m_ticks_last_move{0};
    float m_movem_spd{2.0f};
    point m_dest{-1, -1};
  };
}