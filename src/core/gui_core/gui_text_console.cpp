/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "gui_text_console.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace Forradia {
  void GUITextConsole::RenderDerived() const {
    GUIPanel::RenderDerived();
    auto bounds{GetBounds()};
    auto y{bounds.y + k_margin};
    for (auto &textLine : m_textLines) {
      GetSingleton<TextRenderer>().DrawString(textLine, bounds.x + k_margin, y);
      y += k_lineHeight;
    }
    auto separatorRect{RectF{bounds.x, bounds.y + bounds.height - k_lineHeight,
                             bounds.width, k_separatorHeight}};
    GetSingleton<ImageRenderer>().DrawImage(
        "Black", separatorRect.x, separatorRect.y, separatorRect.width,
        separatorRect.height);
  }

  void GUITextConsole::Print(StringView text) {
    m_textLines.push_back(text.data());
  }
}