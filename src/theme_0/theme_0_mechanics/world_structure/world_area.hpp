/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class tile;
  class creature;

  class world_area {
  public:
    world_area() { initialize(); }

    size get_size() const;

    bool is_valid_coordinate(int x, int y) const;

    s_ptr<tile> get_tile(int x, int y) const;

    s_ptr<tile> get_tile(point coordinate) const;

    auto &get_creatures_mirror_ref() { return m_creaturesMirror; }

  private:
    void initialize();

    vec<vec<s_ptr<tile>>> m_tiles;
    std::map<s_ptr<creature>, point> m_creaturesMirror;
  };
}