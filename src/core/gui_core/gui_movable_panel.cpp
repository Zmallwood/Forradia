/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_movable_panel.hpp"
#include "core/cursor/cursor.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace forr {
  void gui_movable_panel::UpdateDerived() {
    auto mousePosition{GetNormalizedMousePosition()};
    auto draggableArea{GetDraggableArea()};
    if (draggableArea.Contains(mousePosition)) {
      GetSingleton<cursor>().SetCursorStyle(cursor_styles::HoveringClickableGUI);
      if (GetSingleton<mouse_input>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredPickResult()) {
        StartMoving();
      }
    }
    if (GetSingleton<mouse_input>()
            .GetLeftMouseButtonRef()
            .GetHasBeenReleasedDontPickResult()) {
      StopMoving();
    }
    auto bounds{GetBounds()};
    if (bounds.Contains(mousePosition)) {
      if (GetSingleton<mouse_input>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredDontPickResult()) {
        GetSingleton<mouse_input>().GetLeftMouseButtonRef().Reset();
      }
    }
    if (GetIsBeingMoved()) {
      auto moveStartPosition{GetMoveStartPosition()};
      auto moveStartMousePosition{GetMoveStartMousePosition()};
      auto currentMousePosition{GetNormalizedMousePosition()};
      auto newPosition{moveStartPosition + currentMousePosition -
                       moveStartMousePosition};
      SetPosition(newPosition);
    }
  }

  void gui_movable_panel::StartMoving() {
    m_isBeingMoved = true;
    m_moveStartPosition = GetBounds().GetPosition();
    m_moveStartMousePosition = GetNormalizedMousePosition();
  }

  void gui_movable_panel::StopMoving() { m_isBeingMoved = false; }

  rect_f gui_movable_panel::GetDraggableArea() { return GetBounds(); }
}