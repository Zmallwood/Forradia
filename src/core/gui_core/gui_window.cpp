/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "core/rendering/text/sub/font_sizes.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_window_title_bar::render() const {
    auto parent_window_bounds{m_parent_window.get_bounds()};
    get_singleton<image_renderer>().draw_image(
        "GUIWindowTitleBarBackground", parent_window_bounds.x,
        parent_window_bounds.y, parent_window_bounds.w, k_height);
    get_singleton<text_renderer>().draw_string(
        k_window_title_text, parent_window_bounds.x + 0.01f,
        parent_window_bounds.y + 0.01f, font_sizes::_20, false, colors::yellow);
  }

  rect_f gui_window_title_bar::get_bounds() const {
    rect_f bounds_result;
    auto parent_window_bounds{m_parent_window.get_bounds()};
    bounds_result.x = parent_window_bounds.x;
    bounds_result.y = parent_window_bounds.y;
    bounds_result.w = parent_window_bounds.w;
    bounds_result.h = k_height;
    return bounds_result;
  }
  void gui_window::initialize() { set_visible(false); }

  void gui_window::render_derived() const {
    gui_movable_panel::render_derived();
    m_gui_window_title_bar.render();
  }

  rect_f gui_window::get_draggable_area() {
    return m_gui_window_title_bar.get_bounds();
  }
}