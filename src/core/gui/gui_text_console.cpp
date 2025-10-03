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
    auto b{get_bounds()};
    auto max_num_lines{c_int(b.h / k_line_h - 1)};
    auto y{b.y + k_marg};
    for (auto i = 0; i < max_num_lines; i++) {
      auto idx{m_lines.size() - max_num_lines + i};
      if (idx < 0 || idx >= m_lines.size()) {
        continue;
      }
      auto text_line = m_lines.at(idx);
      get_ston<text_renderer>().draw_str(text_line, b.x + k_marg, y);
      y += k_line_h;
    }
    auto sep_rect{rect_f{b.x, b.y + b.h - k_line_h, b.w, k_sep_h}};
    get_ston<image_renderer>().draw_img("Black", sep_rect.x, sep_rect.y,
                                          sep_rect.w, sep_rect.h);
  }

  void gui_text_console::print(str_view text) {
    m_lines.push_back(text.data());
  }
}