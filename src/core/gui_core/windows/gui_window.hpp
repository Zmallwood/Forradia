/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../gui_movable_panel.hpp"
#include "sub/gui_window_title_bar.hpp"

namespace forr {
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

    //const float k_title_bar_height{0.04f};

    gui_window_title_bar m_gui_window_title_bar;
  };
}
