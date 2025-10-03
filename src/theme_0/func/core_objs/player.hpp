/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "sub/player_body.hpp"

namespace forr {
  class player {
   public:
    player() { init(); }

    void move_n();

    void move_e();

    void move_s();

    void move_w();

    auto get_name() const { return m_name; }

    auto get_pos() const { return m_pos; }

    auto get_movem_spd() const { return m_movem_spd; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int val) { m_ticks_last_move = val; }

    auto get_dest() const { return m_dest; }

    void set_dest(point val) { m_dest = val; }

    auto &get_body_ref() { return m_body; }

    auto get_money() const { return m_money; }

   private:
    void init();

    void move_to_suitable_pos();

    str m_name{"Unnamed Player"};
    point m_pos{60, 50};
    float m_movem_spd{5.0f};
    int m_ticks_last_move{0};
    point m_dest{-1, -1};
    player_body m_body;
    int m_money{0};
  };
}