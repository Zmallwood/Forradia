/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  sz_f calc_tl_sz();

  float calc_tl_sz_new();

  sz calc_grid_sz();

  enum class body_part_types { none, overall_body, right_arm, left_arm, legs };

  class body_part {
   public:
    auto str() const { return str_; }
    auto curr_energy() const { return curr_energy_; }
    auto max_energy() const { return max_energy_; }
    auto temp() const { return temp_; }

   private:
    float str_{0.1f};
    float curr_energy_{1.0f};
    float max_energy_{1.0f};
    float temp_{37.0f};
  };

  class player_body {
   public:
    player_body() { init(); }

    body_part *body_part_ptr(body_part_types type);

   private:
    void init();

    std::map<body_part_types, body_part> parts_;
  };

  class player {
   public:
    player() { init(); }

    void move_n();

    void move_e();

    void move_s();

    void move_w();

    auto name() const { return name_; }

    auto pos() const { return pos_; }

    auto movem_spd() const { return movem_spd_; }

    auto ticks_last_move() const { return ticks_last_move_; }

    void set_ticks_last_move(int val) { ticks_last_move_ = val; }

    auto dest() const { return dest_; }

    void set_dest(pt val) { dest_ = val; }

    auto &body_ref() { return body_; }

    auto money() const { return money_; }

   private:
    void init();

    void move_to_suitable_pos();

    str name_{"Unnamed Player"};
    pt pos_{60, 50};
    float movem_spd_{5.0f};
    int ticks_last_move_{0};
    pt dest_{-1, -1};
    player_body body_;
    int money_{0};
  };
}