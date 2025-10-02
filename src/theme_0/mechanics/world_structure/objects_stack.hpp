/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class object;

  class objects_stack {
  public:
    void clear_objects();

    void add_object(str_view object_type_name);

    void add_tree_object(str_view object_type_name);

    int get_size() const;

    auto get_objects() const { return m_objects; }

  private:
    vec<s_ptr<object>> m_objects;
  };
}