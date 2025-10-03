/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_struct.hpp"

namespace forr {
  void creature::init() { m_movem_spd *= (rand_int(3) + 1) / 2.0f; }

  void npc::init() {
    gen_name();

    m_ticks_next_spontaneous_speech =
        get_ticks() + rand_int(300 * k_one_sec_millis);
  }

  void npc::gen_name() {
    vec<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};
    vec<char> consonants{'q', 'w', 'r', 't', 'p', 's', 'd', 'f', 'g', 'h',
                         'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    char c0{vowels.at(rand_int(vowels.size()))};
    char c1{consonants.at(rand_int(consonants.size()))};
    char c2{consonants.at(rand_int(consonants.size()))};
    char c3{vowels.at(rand_int(vowels.size()))};
    char c4{consonants.at(rand_int(consonants.size()))};
    char c5{consonants.at(rand_int(consonants.size()))};
    char c6{vowels.at(rand_int(vowels.size()))};

    m_name = str() + c0 + c1 + c2 + c3 + c4 + c5 + c6;
  }

  void tree_object::init(str_view obj_type_name) {
    if (obj_type_name != "ObjectFirTree" &&
        obj_type_name != "ObjectBirchTree") {
      return;
    }
    int num_trunk_parts;
    if (obj_type_name == "ObjectFirTree") {
      num_trunk_parts = 55 + rand_int(44);
    } else if (obj_type_name == "ObjectBirchTree") {
      num_trunk_parts = 25 + rand_int(14);
    }
    m_w_factor *= (rand_int(5) + 1) / 2.0f + 1.0f;
    auto offs_x{0.0f};
    for (auto i = 0; i < num_trunk_parts; i++) {
      offs_x += (rand_int(20) - 10) / 100.0f;
      auto offset_y{i * 0.1f};
      auto pos{point_f{offs_x, offset_y}};
      auto needles_type{rand_int(5)};
      m_trunk_parts.push_back(pos);
      str needles_name;
      if (obj_type_name == "ObjectFirTree") {
        needles_name = "ObjectFirTreeNeedles";
      } else if (obj_type_name == "ObjectBirchTree") {
        if (i % 4 != 0) {
          m_needle_types.push_back(0);
          continue;
        }
        needles_name = "ObjectBirchTreeBranch";
      }
      m_needle_types.push_back(
          needles_type ? hash(needles_name + std::to_string(needles_type)) : 0);
    }
  }

  void objects_stack::clear_objs() { m_objects.clear(); }

  void objects_stack::add_obj(str_view obj_type_name) {
    m_objects.push_back(std::make_shared<object>(obj_type_name));
  }

  void objects_stack::add_tree_obj(str_view obj_type_name) {
    m_objects.push_back(std::make_shared<tree_object>(obj_type_name));
  }

  int objects_stack::get_sz() const { return m_objects.size(); }

  void tile::init() { m_objects_stack = std::make_shared<objects_stack>(); }

  void tile::set_ground(str_view ground_name) { m_ground = hash(ground_name); }

  void world_area::init(size w_area_sz, float world_scaling) {
    auto sz{w_area_sz};
    sz.w *= world_scaling;
    sz.h *= world_scaling;
    for (auto x = 0; x < sz.w; x++) {
      m_tiles.push_back(vec<std::shared_ptr<tile>>());
      for (auto y = 0; y < sz.h; y++) {
        m_tiles[x].push_back(std::make_shared<tile>());
      }
    }
  }

  size world_area::get_sz() const { 
    auto w{c_int(m_tiles.size())};
    auto h{0};
    if (w) {
      h = m_tiles.at(0).size();
    }
    return {w, h};
  }

  bool world_area::is_valid_coord(int x, int y) const {
    auto sz{get_sz()};
    return x >= 0 && y >= 0 && x < sz.w && y < sz.h;
  }

  s_ptr<tile> world_area::get_tl(int x, int y) const {
    if (is_valid_coord(x, y)) {
      return m_tiles.at(x).at(y);
    }
    return nullptr;
  }

  s_ptr<tile> world_area::get_tl(point coord) const {
    return get_tl(coord.x, coord.y);
  }

  void world::init(size w_area_sz, float world_scaling) {
    m_curr_w_area = std::make_shared<world_area>(w_area_sz, world_scaling);
  }
}