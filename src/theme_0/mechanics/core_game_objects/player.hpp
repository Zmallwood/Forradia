/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "sub/player_body.hpp"

namespace forr {
  class player {
   public:
    player() { initialize(); }

    void move_north();

    void move_east();

    void move_south();

    void move_west();

    auto get_name() const { return m_name; }

    auto get_position() const { return m_pos; }

    auto get_movement_speed() const { return m_movem_spd; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int val) { m_ticks_last_move = val; }

    auto get_destination() const { return m_dest; }

    void set_destination(point val) { m_dest = val; }

    auto &get_player_body_ref() { return m_body; }

    auto get_money() const { return m_money; }

   private:
    void initialize();

    void move_to_suitable_position();

    str m_name{"Unnamed Player"};
    point m_pos{60, 50};
    float m_movem_spd{5.0f};
    int m_ticks_last_move{0};
    point m_dest{-1, -1};
    player_body m_body;
    int m_money{0};
  };
}