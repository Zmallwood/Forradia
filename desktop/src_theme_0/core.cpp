/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"
#include "engine.hpp"
#include "game_props.hpp"
#include "world_struct.hpp"

_NS_START_
sz_f calc_tl_sz() {
  auto num_grid_rows{_<game_props>().k_num_grid_rows};
  auto tl_h{1.0f / num_grid_rows};
  auto asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
  auto tl_w{tl_h / asp_rat};
  return {tl_w, tl_h};
}

float calc_tl_sz_new() { return 1.0f / _<game_props>().k_num_grid_rows; }

sz calc_grid_sz() {
  auto tl_sz{calc_tl_sz_new()};
  auto num_grid_cols{c_int(1.0f / tl_sz) + 1};
  auto num_grid_rows{_<game_props>().k_num_grid_rows};
  return {num_grid_cols, num_grid_rows};
}

void player_body::init() {
  parts_.insert({body_part_types::overall_body, body_part()});
  parts_.insert({body_part_types::right_arm, body_part()});
  parts_.insert({body_part_types::left_arm, body_part()});
  parts_.insert({body_part_types::legs, body_part()});
}

body_part *player_body::body_part_ptr(body_part_types type) {
  if (parts_.contains(type))
    return &parts_.at(type);
  return nullptr;
}

void player::init() { move_to_suitable_pos(); }

void player::move_to_suitable_pos() {
  auto w_area{_<world>().curr_w_area()};
  auto sz{w_area->get_sz()};
  pos_ = {sz.w / 2, sz.h / 2};
  while (w_area->get_tl(pos_)->ground() == hash("ground_water"))
    pos_ = {rand_int(sz.w), rand_int(sz.h)};
}

void player::move_n() { pos_.y -= 1; }

void player::move_e() { pos_.x += 1; }

void player::move_s() { pos_.y += 1; }

void player::move_w() { pos_.x -= 1; }
_NS_END_