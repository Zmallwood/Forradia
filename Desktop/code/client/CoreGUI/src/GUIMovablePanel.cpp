//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIMovablePanel.hpp"
#include "Cursor.hpp"
#include "Mouse/MouseInput.hpp"
#include "SDLDevice.hpp"

namespace Forradia
{
    void GUIMovablePanel::UpdateDerived()
    {
        // Get the normalized mouse position.

        auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

        // Get the drag area, which is the area where the panel can be moved.

        auto draggableArea{this->GetDraggableArea()};

        // Check if the mouse is over the draggable area.

        if (draggableArea.Contains(mousePosition))
        {
            // Set the cursor to the hovering clickable GUI cursor.

            _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

            // If the left mouse button has been fired.

            if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult())
            {
                // Start moving the panel.

                this->StartMove();
            }
        }

        // Check if the left mouse button has been released.

        if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenReleased())
        {
            // Stop moving the panel (can be called even if this panel is not being moved).

            this->StopMove();
        }

        // Get the bounds of this panel.

        auto bounds{GetBounds()};

        // Check if the mouse is over the bounds of this panel.

        if (bounds.Contains(mousePosition))
        {
            // If the left mouse button has been fired.

            if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired())
            {
                // Reset the left mouse button. This is done to prevent any other mouse actions
                // from being triggered when there has been a mouse click inside this panel.

                _<MouseInput>().GetLeftMouseButtonRef().Reset();
            }
        }

        // If this panel is being moved.

        if (GetIsBeingMoved())
        {
            // Compute the new position of this panel.

            auto newPosition{GetMoveStartingPosition() + mousePosition -
                             GetMoveStartingMousePosition()};

            // Set the new position of this panel.

            this->SetPosition(newPosition);
        }
    }

    void GUIMovablePanel::StartMove()
    {
        // Set the flag that indicates that this panel is being moved.

        m_isBeingMoved = true;

        // Set the starting position of the move.

        m_moveStartingPosition = this->GetBounds().GetPosition();

        // Set the starting mouse position of the move.

        m_moveStartingMousePosition = GetNormallizedMousePosition(_<SDLDevice>().GetWindow());
    }

    void GUIMovablePanel::StopMove()
    {
        // Set the flag to indicatee that this panel is not being moved.

        m_isBeingMoved = false;
    }

    RectF GUIMovablePanel::GetDraggableArea() const
    {
        // Set the draggable area to the bounds of this panel as default. This can be overridden
        // by derived classes.

        return this->GetBounds();
    }
}