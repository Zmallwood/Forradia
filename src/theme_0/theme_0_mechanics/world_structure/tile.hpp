/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "directions.hpp"

namespace forr {
  class objects_stack;
  class creature;

  class tile {
  public:
    tile() { initialize(); }

    void set_ground(str_view ground_name);

    auto get_ground() const { return m_ground; }

    auto get_objects_stack() const { return m_objects_stack; }

    auto get_creature() const { return m_creature; }

    void set_creature(s_ptr<creature> value) { m_creature = value; }

    auto get_elevation() const { return m_elevation; }

    void set_elevation(int value) { m_elevation = value; }

    auto get_water_depth() const { return m_water_depth; }

    void set_water_depth(int value) { m_water_depth = value; }

    auto get_river_direction_1() const { return m_river_direction_1; }

    void set_river_direction_1(directions value) {
      m_river_direction_1 = value;
    }

    auto get_river_direction_2() const { return m_river_direction_2; }

    void set_river_direction_2(directions value) {
      m_river_direction_2 = value;
    }

  private:
    void initialize();

    int m_ground{0};
    s_ptr<objects_stack> m_objects_stack;
    s_ptr<creature> m_creature;
    int m_elevation{0};
    int m_water_depth{0};
    directions m_river_direction_1{directions::none};
    directions m_river_direction_2{directions::none};
  };
}