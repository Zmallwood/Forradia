/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class tile_hovering {
   public:
    void update();

    auto get_hovered_coordinate() const { return m_hovered_coordinate; }

   private:
    point m_hovered_coordinate{-1, -1};
  };
}