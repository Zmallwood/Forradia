/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "gui_label.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace Forradia {
  void GUILabel::RenderDerived() const {
    auto bounds{GetBounds()};
    auto x{bounds.x};
    auto y{bounds.y};
    if (m_centerAlign) {
      bounds.x += bounds.width / 2;
      bounds.y += bounds.height / 2;
    }
    GetSingleton<TextRenderer>().DrawString(
        m_text, bounds.x, bounds.y, FontSizes::_20, m_centerAlign, m_color);
  }
}
