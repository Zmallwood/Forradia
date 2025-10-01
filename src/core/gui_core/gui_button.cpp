/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_button.hpp"
#include "core/cursor/cursor.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_button::UpdateDerived() {
    gui_panel::UpdateDerived();
    auto mousePosition{GetNormalizedMousePosition()};
    auto isHovered{GetBounds().Contains(mousePosition)};
    if (isHovered) {
      SetBackgroundImage(m_hoveredBackgroundImage);
      GetSingleton<cursor>().SetCursorStyle(cursor_styles::HoveringClickableGUI);
      if (GetSingleton<mouse_input>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredPickResult()) {
        m_action();
      }
    } else {
      SetBackgroundImage(m_backgroundImage);
    }
  }

  void gui_button::RenderDerived() const {
    gui_panel::RenderDerived();
    auto bounds{GetBounds()};
    GetSingleton<text_renderer>().DrawString(m_text, bounds.x + bounds.width / 2,
                                            bounds.y + bounds.height / 2,
                                            font_sizes::_20, true);
  }
}
