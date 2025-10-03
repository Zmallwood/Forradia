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
    world_area(size w_area_sz, float world_scaling) {
      init(w_area_sz, world_scaling);
    }

    size get_sz() const;

    bool is_valid_coord(int x, int y) const;

    s_ptr<tile> get_tl(int x, int y) const;

    s_ptr<tile> get_tl(point coord) const;

    auto &get_creatures_mirror_ref() { return m_creatures_mirror; }

    auto &get_npcs_mirror_ref() { return m_npcs_mirror; }

   private:
    void init(size w_area_sz, float world_scaling);

    vec<vec<s_ptr<tile>>> m_tiles;
    std::map<s_ptr<creature>, point> m_creatures_mirror;
    std::map<s_ptr<npc>, point> m_npcs_mirror;
  };
}