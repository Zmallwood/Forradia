/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class npc {
   public:
    npc(str_view type_name) : m_type{hash(type_name)} { init(); }

    auto get_type() const { return m_type; }

    auto get_name() const { return m_name; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int value) { m_ticks_last_move = value; }

    auto get_movem_spd() const { return m_movem_spd; }

    auto get_dest() const { return m_dest; }

    void set_dest(point val) { m_dest = val; }

    auto get_ticks_next_spontaneous_speech() const {
      return m_ticks_next_spontaneous_speech;
    }

    void set_ticks_next_spontaneous_speech(int value) {
      m_ticks_next_spontaneous_speech = value;
    }

   private:
    void init();

    void gen_name();

    int m_type{0};
    str m_name;
    int m_ticks_last_move{0};
    float m_movem_spd{2.0f};
    point m_dest{-1, -1};
    int m_ticks_next_spontaneous_speech{0};
  };
}