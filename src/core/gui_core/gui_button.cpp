/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_button.hpp"
#include "core/cursor/cursor.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_button::update_derived() {
    gui_panel::update_derived();
    auto mousePosition{GetNormalizedMousePosition()};
    auto isHovered{get_bounds().contains(mousePosition)};
    if (isHovered) {
      set_background_image(m_hoveredBackgroundImage);
      GetSingleton<cursor>().set_cursor_style(
          cursor_styles::HoveringClickableGUI);
      if (GetSingleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_pick_result()) {
        m_action();
      }
    } else {
      set_background_image(m_backgroundImage);
    }
  }

  void gui_button::render_derived() const {
    gui_panel::render_derived();
    auto bounds{get_bounds()};
    GetSingleton<text_renderer>().draw_string(
        m_text, bounds.x + bounds.width / 2, bounds.y + bounds.height / 2,
        font_sizes::_20, true);
  }
}
