/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class tile;
  class creature;
  class npc;

  class world_area {
   public:
    world_area() { initialize(); }

    size get_size() const;

    bool is_valid_coordinate(int x, int y) const;

    s_ptr<tile> get_tile(int x, int y) const;

    s_ptr<tile> get_tile(point coord) const;

    auto &get_creatures_mirror_ref() { return m_creatures_mirror; }

    auto &get_npcs_mirror_ref() { return m_npcs_mirror; }

   private:
    void initialize();

    vec<vec<s_ptr<tile>>> m_tiles;
    std::map<s_ptr<creature>, point> m_creatures_mirror;
    std::map<s_ptr<npc>, point> m_npcs_mirror;
  };
}