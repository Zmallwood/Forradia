/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_button.hpp"
#include "core/core.hpp"
#include "core/input.hpp"
#include "core/rend/text/text_renderer.hpp"

namespace forr {
  void gui_button::update_derived() {
    gui_panel::update_derived();
    auto mouse_pos{get_norm_mouse_pos()};
    auto hovered{get_bounds().contains(mouse_pos)};
    if (hovered) {
      set_bg_img(m_hovered_bg_img);
      get_ston<cursor>().set_curs_style(
          cursor_styles::hovering_clickable_gui);
      if (get_ston<mouse_input>()
              .get_left_btn_ref()
              .get_been_fired_pick_result()) {
        m_action();
      }
    } else {
      set_bg_img(m_bg_img);
    }
  }

  void gui_button::render_derived() const {
    gui_panel::render_derived();
    auto b{get_bounds()};
    get_ston<text_renderer>().draw_str(m_text, b.x + b.w / 2, b.y + b.h / 2,
                                          font_sizes::_20, true);
  }
}
