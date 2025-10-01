/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_movable_panel.hpp"
#include "core/cursor/cursor.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace forr {
  void gui_movable_panel::update_derived() {
    auto mousePosition{GetNormalizedMousePosition()};
    auto draggableArea{get_draggable_area()};
    if (draggableArea.contains(mousePosition)) {
      GetSingleton<cursor>().set_cursor_style(
          cursor_styles::HoveringClickableGUI);
      if (GetSingleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_pick_result()) {
        start_moving();
      }
    }
    if (GetSingleton<mouse_input>()
            .get_left_mouse_button_ref()
            .get_has_been_released_dont_pick_result()) {
      stop_moving();
    }
    auto bounds{get_bounds()};
    if (bounds.contains(mousePosition)) {
      if (GetSingleton<mouse_input>()
              .get_left_mouse_button_ref()
              .get_has_been_fired_dont_pick_result()) {
        GetSingleton<mouse_input>().get_left_mouse_button_ref().reset();
      }
    }
    if (get_is_being_moved()) {
      auto moveStartPosition{get_move_start_position()};
      auto moveStartMousePosition{get_move_start_mouse_position()};
      auto currentMousePosition{GetNormalizedMousePosition()};
      auto newPosition{moveStartPosition + currentMousePosition -
                       moveStartMousePosition};
      set_position(newPosition);
    }
  }

  void gui_movable_panel::start_moving() {
    m_isBeingMoved = true;
    m_moveStartPosition = get_bounds().get_position();
    m_moveStartMousePosition = GetNormalizedMousePosition();
  }

  void gui_movable_panel::stop_moving() { m_isBeingMoved = false; }

  rect_f gui_movable_panel::get_draggable_area() { return get_bounds(); }
}