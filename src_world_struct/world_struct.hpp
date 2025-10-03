/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "comm.hpp"

namespace forr {
  enum class directions {
    none,
    north,
    east,
    south,
    west,
    north_east,
    south_east,
    south_west,
    north_west
  };

  class creature {
   public:
    creature(str_view type_name) : m_type{hash(type_name)} { init(); }

    auto get_type() const { return m_type; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int value) { m_ticks_last_move = value; }

    auto get_movem_spd() const { return m_movem_spd; }

    auto get_dest() const { return m_dest; }

    void set_dest(pt val) { m_dest = val; }

   private:
    void init();

    int m_type{0};
    int m_ticks_last_move{0};
    float m_movem_spd{2.0f};
    pt m_dest{-1, -1};
  };

  class npc {
   public:
    npc(str_view type_name) : m_type{hash(type_name)} { init(); }

    auto get_type() const { return m_type; }

    auto get_name() const { return m_name; }

    auto get_ticks_last_move() const { return m_ticks_last_move; }

    void set_ticks_last_move(int value) { m_ticks_last_move = value; }

    auto get_movem_spd() const { return m_movem_spd; }

    auto get_dest() const { return m_dest; }

    void set_dest(pt val) { m_dest = val; }

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
    pt m_dest{-1, -1};
    int m_ticks_next_spontaneous_speech{0};
  };

  class object {
   public:
    object(str_view object_type_name) : m_type(hash(object_type_name)) {}

    auto get_type() const { return m_type; }

   private:
    int m_type{0};
  };

  class tree_object : public object {
   public:
    tree_object(str_view obj_type_name) : object(obj_type_name) {
      init(obj_type_name);
    }

    auto get_trunk_parts() const { return m_trunk_parts; }

    auto get_needle_types() const { return m_needle_types; }

    auto get_w_factor() const { return m_w_factor; }

   private:
    void init(str_view obj_type_name);

    vec<pt_f> m_trunk_parts;
    vec<int> m_needle_types;
    float m_w_factor{1.0f};
  };

  class objects_stack {
   public:
    void clear_objs();

    void add_obj(str_view obj_type_name);

    void add_tree_obj(str_view obj_type_name);

    int get_sz() const;

    auto get_objs() const { return m_objects; }

   private:
    vec<s_ptr<object>> m_objects;
  };

  class tile {
   public:
    tile() { init(); }

    void set_ground(str_view ground_name);

    auto get_ground() const { return m_ground; }

    auto get_objects_stack() const { return m_objects_stack; }

    auto get_creature() const { return m_creature; }

    void set_creature(s_ptr<creature> val) { m_creature = val; }

    auto get_npc() const { return m_npc; }

    void set_npc(s_ptr<npc> val) { m_npc = val; }

    auto get_elev() const { return m_elev; }

    void set_elev(int val) { m_elev = val; }

    auto get_water_depth() const { return m_water_depth; }

    void set_water_depth(int val) { m_water_depth = val; }

    auto get_river_dir_1() const { return m_river_dir_1; }

    void set_river_dir_1(directions val) { m_river_dir_1 = val; }

    auto get_river_dir_2() const { return m_river_dir_2; }

    void set_river_dir_2(directions val) { m_river_dir_2 = val; }

   private:
    void init();

    int m_ground{0};
    s_ptr<objects_stack> m_objects_stack;
    s_ptr<creature> m_creature;
    s_ptr<npc> m_npc;
    int m_elev{0};
    int m_water_depth{0};
    directions m_river_dir_1{directions::none};
    directions m_river_dir_2{directions::none};
  };

  class world_area {
   public:
    world_area(sz w_area_sz, float world_scaling) {
      init(w_area_sz, world_scaling);
    }

    sz get_sz() const;

    bool is_valid_coord(int x, int y) const;

    s_ptr<tile> get_tl(int x, int y) const;

    s_ptr<tile> get_tl(pt coord) const;

    auto &get_creatures_mirror_ref() { return m_creatures_mirror; }

    auto &get_npcs_mirror_ref() { return m_npcs_mirror; }

   private:
    void init(sz w_area_sz, float world_scaling);

    vec<vec<s_ptr<tile>>> m_tiles;
    std::map<s_ptr<creature>, pt> m_creatures_mirror;
    std::map<s_ptr<npc>, pt> m_npcs_mirror;
  };

  class world {
   public:
    void init(sz w_area_sz, float world_scaling);

    auto get_curr_w_area() const { return m_curr_w_area; }

   private:
    s_ptr<world_area> m_curr_w_area;
  };
}