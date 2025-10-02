/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_text_console.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_text_console::render_derived() const {
    gui_panel::render_derived();
    auto bounds{get_bounds()};
    auto y{bounds.y + k_margin};
    for (auto &text_line : m_text_lines) {
      get_singleton<text_renderer>().draw_string(text_line, bounds.x + k_margin,
                                                 y);
      y += k_line_height;
    }
    auto separator_rect{rect_f{bounds.x, bounds.y + bounds.h - k_line_height,
                               bounds.w, k_separator_height}};
    get_singleton<image_renderer>().draw_image(
        "Black", separator_rect.x, separator_rect.y, separator_rect.w,
        separator_rect.h);
  }

  void gui_text_console::print(str_view text) {
    m_text_lines.push_back(text.data());
  }
}