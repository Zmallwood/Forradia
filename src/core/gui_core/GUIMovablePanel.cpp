/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIMovablePanel.hpp"
#include "core/cursor/Cursor.hpp"
#include "core/input/mouse/MouseInput.hpp"

namespace Forradia {
  void GUIMovablePanel::UpdateDerived() {
    auto mousePosition{GetNormalizedMousePosition()};

    auto draggableArea{GetDraggableArea()};

    if (draggableArea.Contains(mousePosition)) {
      GetSingleton<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

      if (GetSingleton<MouseInput>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredPickResult()) {
        StartMoving();
      }
    }

    if (GetSingleton<MouseInput>()
            .GetLeftMouseButtonRef()
            .GetHasBeenReleasedDontPickResult()) {
      StopMoving();
    }

    auto bounds{GetBounds()};

    if (bounds.Contains(mousePosition)) {
      if (GetSingleton<MouseInput>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredDontPickResult()) {
        GetSingleton<MouseInput>().GetLeftMouseButtonRef().Reset();
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

  void GUIMovablePanel::StartMoving() {
    m_isBeingMoved = true;

    m_moveStartPosition = GetBounds().GetPosition();
    m_moveStartMousePosition = GetNormalizedMousePosition();
  }

  void GUIMovablePanel::StopMoving() { m_isBeingMoved = false; }

  RectF GUIMovablePanel::GetDraggableArea() { return GetBounds(); }
}