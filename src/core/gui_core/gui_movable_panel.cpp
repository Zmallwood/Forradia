/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_movable_panel.hpp"
#include "core/cursor/cursor.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace forr {
  void gui_movable_panel::update_derived() {
    auto mouse_position{get_normalized_mouse_position()};
    auto draggable_area{get_draggable_area()};
    if (draggable_area.contains(mouse_position)) {
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
    auto bounds{get_bounds()};
    if (bounds.contains(mouse_position)) {
      if (get_singleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_dont_pick_result()) {
        get_singleton<mouse_input>().get_left_mouse_button_ref().reset();
      }
    }
    if (get_is_being_moved()) {
      auto move_start_position{get_move_start_position()};
      auto move_start_mouse_position{get_move_start_mouse_position()};
      auto current_mouse_position{get_normalized_mouse_position()};
      auto new_position{move_start_position + current_mouse_position -
                        move_start_mouse_position};
      set_position(new_position);
    }
  }

  void gui_movable_panel::start_moving() {
    m_is_being_moved = true;
    m_move_start_position = get_bounds().get_position();
    m_move_start_mouse_position = get_normalized_mouse_position();
  }

  void gui_movable_panel::stop_moving() { m_is_being_moved = false; }

  rect_f gui_movable_panel::get_draggable_area() { return get_bounds(); }
}