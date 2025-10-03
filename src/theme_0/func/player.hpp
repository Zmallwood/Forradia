/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  enum class body_part_types { none, overall_body, right_arm, left_arm, legs };

  class body_part {
   public:
    auto get_str() const { return m_str; }
    auto get_curr_energy() const { return m_curr_energy; }
    auto get_max_energy() const { return m_max_energy; }
    auto get_temp() const { return m_temp; }

   private:
    float m_str{0.1f};
    float m_curr_energy{1.0f};
    float m_max_energy{1.0f};
    float m_temp{37.0f};
  };

  class player_body {
   public:
    player_body() { init(); }

    body_part *get_body_part_ptr(body_part_types type);

   private:
    void init();

    std::map<body_part_types, body_part> m_parts;
  };

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