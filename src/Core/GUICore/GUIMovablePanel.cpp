/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIMovablePanel.hpp"
#include "Core/Cursor/Cursor.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"

namespace Forradia {
  void GUIMovablePanel::UpdateDerived() {
    auto mousePosition{GetNormalizedMousePosition()};

    auto draggableArea{GetDraggableArea()};

    if (draggableArea.Contains(mousePosition)) {
      _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

      if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenFiredPickResult()) {
        StartMoving();
      }
    }

    if (_<MouseInput>()
            .GetLeftMouseButtonRef()
            .GetHasBeenReleasedDontPickResult()) {
      StopMoving();
    }

    auto bounds{GetBounds()};

    if (bounds.Contains(mousePosition)) {
      if (_<MouseInput>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredDontPickResult()) {
        _<MouseInput>().GetLeftMouseButtonRef().Reset();
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