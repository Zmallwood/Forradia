/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_text_console.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "core/rend/text/text_renderer.hpp"

namespace forr {
  void gui_text_console::render_derived() const {
    gui_panel::render_derived();
    auto bounds{get_bounds()};
    auto max_num_lines{c_int(bounds.h / k_line_height - 1)};
    auto y{bounds.y + k_margin};
    for (auto i = 0; i < max_num_lines; i++) {
      auto idx{m_text_lines.size() - max_num_lines + i};
      if (idx < 0 || idx >= m_text_lines.size()) {
        continue;
      }
      auto text_line = m_text_lines.at(idx);
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