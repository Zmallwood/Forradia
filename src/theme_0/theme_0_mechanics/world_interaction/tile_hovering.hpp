/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class tile_hovering {
  public:
    void Update();

    auto GetHoveredCoordinate() const { return m_hoveredCoordinate; }

  private:
    point m_hoveredCoordinate{-1, -1};
  };
}