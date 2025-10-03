/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "directions.hpp"

namespace forr {
  class objects_stack;
  class creature;
  class npc;

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
}