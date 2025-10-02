/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_movable_panel.hpp"
#include "core/cursor/cursor.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace forr {
  void gui_movable_panel::update_derived() {
    auto mousePosition{get_normalized_mouse_position()};
    auto draggableArea{get_draggable_area()};
    if (draggableArea.contains(mousePosition)) {
      get_singleton<cursor>().set_cursor_style(
          cursor_styles::HoveringClickableGUI);
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
    if (bounds.contains(mousePosition)) {
      if (get_singleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_dont_pick_result()) {
        get_singleton<mouse_input>().get_left_mouse_button_ref().reset();
      }
    }
    if (get_is_being_moved()) {
      auto moveStartPosition{get_move_start_position()};
      auto moveStartMousePosition{get_move_start_mouse_position()};
      auto currentMousePosition{get_normalized_mouse_position()};
      auto newPosition{moveStartPosition + currentMousePosition -
                       moveStartMousePosition};
      set_position(newPosition);
    }
  }

  void gui_movable_panel::start_moving() {
    m_isBeingMoved = true;
    m_moveStartPosition = get_bounds().get_position();
    m_moveStartMousePosition = get_normalized_mouse_position();
  }

  void gui_movable_panel::stop_moving() { m_isBeingMoved = false; }

  rect_f gui_movable_panel::get_draggable_area() { return get_bounds(); }
}