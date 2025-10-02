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
    gui_window_title_bar(gui_window &parent_window, str_view window_title_text)
        : m_parent_window(parent_window),
          k_window_title_text(window_title_text) {}

    void render() const;

    rect_f get_bounds() const;

   private:
    inline static const float k_height{0.04f};
    const str k_window_title_text;

    gui_window &m_parent_window;
  };

  class gui_window : public gui_movable_panel {
   public:
    gui_window(float x, float y, float width, float height,
               str_view window_title_text)
        : gui_movable_panel(x, y, width, height),
          m_gui_window_title_bar(*this, window_title_text) {
      initialize();
    }

   protected:
    void render_derived() const override;

    rect_f get_draggable_area() override;

   private:
    void initialize();

    gui_window_title_bar m_gui_window_title_bar;
  };
}
