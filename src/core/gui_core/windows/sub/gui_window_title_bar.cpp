/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window_title_bar.hpp"
#include "../gui_window.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_window_title_bar::Render() const {
    auto parentWindowBounds{m_parentWindow.GetBounds()};
    GetSingleton<image_renderer>().DrawImage(
        "GUIWindowTitleBarBackground", parentWindowBounds.x,
        parentWindowBounds.y, parentWindowBounds.width, k_height);
    GetSingleton<text_renderer>().DrawString(
        k_windowTitleText, parentWindowBounds.x + 0.01f,
        parentWindowBounds.y + 0.01f, font_sizes::_20, false, colors::Yellow);
  }

  rect_f gui_window_title_bar::GetBounds() const {
    rect_f boundsResult;
    auto parentWindowBounds{m_parentWindow.GetBounds()};
    boundsResult.x = parentWindowBounds.x;
    boundsResult.y = parentWindowBounds.y;
    boundsResult.width = parentWindowBounds.width;
    boundsResult.height = k_height;
    return boundsResult;
  }
}