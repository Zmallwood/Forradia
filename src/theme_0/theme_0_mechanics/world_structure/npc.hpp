/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class npc {
  public:
    npc(str_view type_name) : m_type{hash(type_name)} { initialize(); }

    auto get_type() const { return m_type; }

  private:
    void initialize();

    void generate_name();

    int m_type{0};
    str m_name;
  };
}