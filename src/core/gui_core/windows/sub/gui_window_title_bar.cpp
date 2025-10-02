/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window_title_bar.hpp"
#include "../gui_window.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_window_title_bar::render() const {
    auto parentWindowBounds{m_parentWindow.get_bounds()};
    get_singleton<image_renderer>().draw_image(
        "GUIWindowTitleBarBackground", parentWindowBounds.x,
        parentWindowBounds.y, parentWindowBounds.width, k_height);
    get_singleton<text_renderer>().draw_string(
        k_windowTitleText, parentWindowBounds.x + 0.01f,
        parentWindowBounds.y + 0.01f, font_sizes::_20, false, colors::Yellow);
  }

  rect_f gui_window_title_bar::get_bounds() const {
    rect_f boundsResult;
    auto parentWindowBounds{m_parentWindow.get_bounds()};
    boundsResult.x = parentWindowBounds.x;
    boundsResult.y = parentWindowBounds.y;
    boundsResult.width = parentWindowBounds.width;
    boundsResult.height = k_height;
    return boundsResult;
  }
}