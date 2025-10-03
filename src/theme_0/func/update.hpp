/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  void update_kb_actions();

  void update_kb_movem();

  void update_mouse_movem();

  void update_crea_movem();

  void update_npcs();

  class tile_hovering {
   public:
    void update();

    auto get_hovered_coord() const { return m_hovered_coord; }

   private:
    point m_hovered_coord{-1, -1};
  };
}