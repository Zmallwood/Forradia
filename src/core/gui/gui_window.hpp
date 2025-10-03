/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_movable_panel.hpp"

namespace forr {
  class gui_window;

  class gui_window_title_bar {
   public:
    gui_window_title_bar(gui_window &parent_win, str_view win_title)
        : m_parent_win(parent_win), k_win_title(win_title) {}

    void render() const;

    rect_f get_bounds() const;

   private:
    inline static const float k_h{0.04f};
    const str k_win_title;

    gui_window &m_parent_win;
  };

  class gui_window : public gui_movable_panel {
   public:
    gui_window(float x, float y, float w, float h, str_view win_title)
        : gui_movable_panel(x, y, w, h), m_gui_win_title_bar(*this, win_title) {
      init();
    }

   protected:
    void render_derived() const override;

    rect_f get_drag_area() override;

   private:
    void init();

    gui_window_title_bar m_gui_win_title_bar;
  };
}
