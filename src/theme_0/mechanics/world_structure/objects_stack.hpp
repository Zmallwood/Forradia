/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class object;

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
}