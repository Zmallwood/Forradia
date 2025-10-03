/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "objects_stack.hpp"
#include "object.hpp"
#include "tree_object.hpp"

namespace forr {
  void objects_stack::clear_objects() { m_objects.clear(); }

  void objects_stack::add_object(str_view obj_type_name) {
    m_objects.push_back(std::make_shared<object>(obj_type_name));
  }

  void objects_stack::add_tree_object(str_view obj_type_name) {
    m_objects.push_back(std::make_shared<tree_object>(obj_type_name));
  }

  int objects_stack::get_size() const { return m_objects.size(); }
}