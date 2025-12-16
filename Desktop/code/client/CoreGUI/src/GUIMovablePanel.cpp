/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIMovablePanel.hpp"
#include "Cursor.hpp"
#include "Mouse/MouseInput.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
void GUIMovablePanel::UpdateDerived() {
  auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};
  auto draggableArea{this->GetDraggableArea()};

  if (draggableArea.Contains(mousePosition)) {
    _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

    if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult()) {
      this->StartMove();
    }
  }

  if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenReleased()) {
    this->StopMove();
  }

  auto bounds{GetBounds()};

  if (bounds.Contains(mousePosition)) {
    if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
      // Reset the left mouse button. This is done to prevent any other mouse actions
      // from being triggered when there has been a mouse click inside this panel.
      _<MouseInput>().GetLeftMouseButtonRef().Reset();
    }
  }

  if (GetIsBeingMoved()) {
    auto newPosition{GetMoveStartingPosition() + mousePosition - GetMoveStartingMousePosition()};
    this->SetPosition(newPosition);
  }
}

void GUIMovablePanel::StartMove() {
  m_isBeingMoved = true;
  m_moveStartingPosition = this->GetBounds().GetPosition();
  m_moveStartingMousePosition = GetNormallizedMousePosition(_<SDLDevice>().GetWindow());
}

void GUIMovablePanel::StopMove() {
  m_isBeingMoved = false;
}

RectF GUIMovablePanel::GetDraggableArea() const {
  // Set the draggable area to the bounds of this panel as default. This can be overridden
  // by derived classes.
  return this->GetBounds();
}
}