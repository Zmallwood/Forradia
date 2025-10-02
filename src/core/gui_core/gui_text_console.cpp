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
    for (auto &textLine : m_textLines) {
      get_singleton<text_renderer>().draw_string(textLine, bounds.x + k_margin,
                                                 y);
      y += k_lineHeight;
    }
    auto separatorRect{rect_f{bounds.x, bounds.y + bounds.h - k_lineHeight,
                              bounds.h, k_separatorHeight}};
    get_singleton<image_renderer>().draw_image("Black", separatorRect.x,
                                               separatorRect.y, separatorRect.w,
                                               separatorRect.h);
  }

  void gui_text_console::print(str_view text) {
    m_textLines.push_back(text.data());
  }
}