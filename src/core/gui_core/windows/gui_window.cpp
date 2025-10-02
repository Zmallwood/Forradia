/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window.hpp"

namespace forr {
  void gui_window::initialize() { set_visible(false); }

  void gui_window::render_derived() const {
    gui_movable_panel::render_derived();
    m_gui_window_title_bar.render();
  }

  rect_f gui_window::get_draggable_area() {
    return m_gui_window_title_bar.get_bounds();
  }
}