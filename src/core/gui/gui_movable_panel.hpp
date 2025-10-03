/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_panel.hpp"

namespace forr {
  class gui_movable_panel : public gui_panel {
   public:
    gui_movable_panel(float x, float y, float w, float h)
        : gui_panel(x, y, w, h) {}

   protected:
    void update_derived() override;

    void start_move();

    void stop_move();

    virtual rect_f get_drag_area();

    auto get_being_moved() const { return m_being_moved; }

    auto get_move_start_pos() const { return m_move_start_pos; }

    auto get_move_start_mouse_pos() const { return m_move_start_mouse_pos; }

   private:
    bool m_being_moved{false};
    point_f m_move_start_pos{-1, -1};
    point_f m_move_start_mouse_pos{-1, -1};
  };
}
