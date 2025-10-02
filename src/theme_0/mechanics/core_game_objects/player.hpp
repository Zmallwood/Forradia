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

    auto get_position() const { return m_position; }

    auto get_movement_speed() const { return m_movement_speed; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int value) { m_ticks_last_move = value; }

    auto get_destination() const { return m_destination; }

    void set_destination(point value) { m_destination = value; }

    auto &get_player_body_ref() { return m_player_body; }

    auto get_money() const { return m_money; }

   private:
    void initialize();

    void move_to_suitable_position();

    str m_name{"Unnamed Player"};
    point m_position{60, 50};
    float m_movement_speed{5.0f};
    int m_ticks_last_move{0};
    point m_destination{-1, -1};
    player_body m_player_body;
    int m_money{0};
  };
}