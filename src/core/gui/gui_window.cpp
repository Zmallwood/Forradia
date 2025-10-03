/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "core/rend/text/sub/font_sizes.hpp"
#include "core/rend/text/text_renderer.hpp"

namespace forr {
  void gui_window_title_bar::render() const {
    auto parent_win_b{m_parent_win.get_bounds()};
    get_ston<image_renderer>().draw_img("GUIWindowTitleBarBackground",
                                          parent_win_b.x, parent_win_b.y,
                                          parent_win_b.w, k_h);
    get_ston<text_renderer>().draw_string(
        k_win_title, parent_win_b.x + 0.01f, parent_win_b.y + 0.01f,
        font_sizes::_20, false, colors::yellow);
  }

  rect_f gui_window_title_bar::get_bounds() const {
    rect_f b_res;
    auto parent_win_b{m_parent_win.get_bounds()};
    b_res.x = parent_win_b.x;
    b_res.y = parent_win_b.y;
    b_res.w = parent_win_b.w;
    b_res.h = k_h;
    return b_res;
  }
  void gui_window::init() { set_visible(false); }

  void gui_window::render_derived() const {
    gui_movable_panel::render_derived();
    m_gui_win_title_bar.render();
  }

  rect_f gui_window::get_drag_area() {
    return m_gui_win_title_bar.get_bounds();
  }
}