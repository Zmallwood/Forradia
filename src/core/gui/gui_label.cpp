/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_label.hpp"
#include "core/rend/text/text_renderer.hpp"

namespace forr {
  void gui_label::render_derived() const {
    auto b{get_bounds()};
    auto x{b.x};
    auto y{b.y};
    if (m_cent_align) {
      b.x += b.w / 2;
      b.y += b.h / 2;
    }
    get_ston<text_renderer>().draw_str(m_text, b.x, b.y, font_sizes::_20,
                                          m_cent_align, m_color);
  }
}
