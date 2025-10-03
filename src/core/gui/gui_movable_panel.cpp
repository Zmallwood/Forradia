/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_movable_panel.hpp"
#include "core/core.hpp"
#include "core/input.hpp"

namespace forr {
  void gui_movable_panel::update_derived() {
    auto mouse_pos{get_norm_mouse_pos()};
    auto drag_area{get_drag_area()};
    if (drag_area.contains(mouse_pos)) {
      get_ston<cursor>().set_curs_style(
          cursor_styles::hovering_clickable_gui);
      if (get_ston<mouse_input>()
              .get_left_btn_ref()
              .get_been_fired_pick_result()) {
        start_move();
      }
    }
    if (get_ston<mouse_input>()
            .get_left_btn_ref()
            .get_been_released_dont_pick_result()) {
      stop_move();
    }
    auto b{get_bounds()};
    if (b.contains(mouse_pos)) {
      if (get_ston<mouse_input>()
              .get_left_btn_ref()
              .get_been_fired_dont_pick_result()) {
        get_ston<mouse_input>().get_left_btn_ref().reset();
      }
    }
    if (get_being_moved()) {
      auto move_start_pos{get_move_start_pos()};
      auto move_start_mouse_pos{get_move_start_mouse_pos()};
      auto curr_mouse_pos{get_norm_mouse_pos()};
      auto new_pos{move_start_pos + curr_mouse_pos - move_start_mouse_pos};
      set_pos(new_pos);
    }
  }

  void gui_movable_panel::start_move() {
    m_being_moved = true;
    m_move_start_pos = get_bounds().get_pos();
    m_move_start_mouse_pos = get_norm_mouse_pos();
  }

  void gui_movable_panel::stop_move() { m_being_moved = false; }

  rect_f gui_movable_panel::get_drag_area() { return get_bounds(); }
}