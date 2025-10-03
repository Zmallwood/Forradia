/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_area.hpp"
#include "tile.hpp"

namespace forr {
  void world_area::init(size w_area_sz, float world_scaling) {
    auto sz{w_area_sz};
    sz.w *= world_scaling;
    sz.h *= world_scaling;
    for (auto x = 0; x < sz.w; x++) {
      m_tiles.push_back(vec<std::shared_ptr<tile>>());
      for (auto y = 0; y < sz.h; y++) {
        m_tiles[x].push_back(std::make_shared<tile>());
      }
    }
  }

  size world_area::get_sz() const {
    auto w{c_int(m_tiles.size())};
    auto h{0};
    if (w) {
      h = m_tiles.at(0).size();
    }
    return {w, h};
  }

  bool world_area::is_valid_coord(int x, int y) const {
    auto sz{get_sz()};
    return x >= 0 && y >= 0 && x < sz.w && y < sz.h;
  }

  s_ptr<tile> world_area::get_tl(int x, int y) const {
    if (is_valid_coord(x, y)) {
      return m_tiles.at(x).at(y);
    }
    return nullptr;
  }

  s_ptr<tile> world_area::get_tl(point coord) const {
    return get_tl(coord.x, coord.y);
  }
}