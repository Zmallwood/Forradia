/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_movable_panel.hpp"
#include "core/core.hpp"
#include "core/input.hpp"

namespace forr {
  void gui_movable_panel::update_derived() {
    auto mouse_pos{get_normalized_mouse_position()};
    auto drag_area{get_draggable_area()};
    if (drag_area.contains(mouse_pos)) {
      get_singleton<cursor>().set_cursor_style(
          cursor_styles::hovering_clickable_gui);
      if (get_singleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_pick_result()) {
        start_moving();
      }
    }
    if (get_singleton<mouse_input>()
            .get_left_mouse_button_ref()
            .get_has_been_released_dont_pick_result()) {
      stop_moving();
    }
    auto b{get_bounds()};
    if (b.contains(mouse_pos)) {
      if (get_singleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_dont_pick_result()) {
        get_singleton<mouse_input>().get_left_mouse_button_ref().reset();
      }
    }
    if (get_is_being_moved()) {
      auto move_start_pos{get_move_start_position()};
      auto move_start_mouse_pos{get_move_start_mouse_position()};
      auto curr_mouse_pos{get_normalized_mouse_position()};
      auto new_pos{move_start_pos + curr_mouse_pos - move_start_mouse_pos};
      set_position(new_pos);
    }
  }

  void gui_movable_panel::start_moving() {
    m_being_moved = true;
    m_move_start_pos = get_bounds().get_position();
    m_move_start_mouse_pos = get_normalized_mouse_position();
  }

  void gui_movable_panel::stop_moving() { m_being_moved = false; }

  rect_f gui_movable_panel::get_draggable_area() { return get_bounds(); }
}