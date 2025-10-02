/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_button.hpp"
#include "core/core.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/rendering/text/text_renderer.hpp"

namespace forr {
  void gui_button::update_derived() {
    gui_panel::update_derived();
    auto mouse_position{get_normalized_mouse_position()};
    auto is_hovered{get_bounds().contains(mouse_position)};
    if (is_hovered) {
      set_background_image(m_hovered_background_image);
      get_singleton<cursor>().set_cursor_style(
          cursor_styles::hovering_clickable_gui);
      if (get_singleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_pick_result()) {
        m_action();
      }
    } else {
      set_background_image(m_background_image);
    }
  }

  void gui_button::render_derived() const {
    gui_panel::render_derived();
    auto bounds{get_bounds()};
    get_singleton<text_renderer>().draw_string(m_text, bounds.x + bounds.w / 2,
                                               bounds.y + bounds.h / 2,
                                               font_sizes::_20, true);
  }
}
