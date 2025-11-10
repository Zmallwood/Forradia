//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIMovablePanel.hpp"

#include "SDLDevice.hpp"

#include "Cursor.hpp"

#include "Mouse/MouseInput.hpp"

namespace Forradia
{
    void GUIMovablePanel::UpdateDerived()
    {
        // Get the normalized mouse position.

        auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

        // Get the drag area, which is the area where the panel can be moved.

        auto draggableArea{this->GetDraggableArea()};

        if (draggableArea.Contains(mousePosition))
        {
            _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

            if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult())
            {
                this->StartMove();
            }
        }

        if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenReleased())
        {
            this->StopMove();
        }

        auto bounds{GetBounds()};

        if (bounds.Contains(mousePosition))
        {
            if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired())
            {
                _<MouseInput>().GetLeftMouseButtonRef().Reset();
            }
        }
        if (GetIsBeingMoved())
        {
            auto currentMousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

            auto newPosition{GetMoveStartingPosition() + currentMousePosition -
                             GetMoveStartingMousePosition()};

            this->SetPosition(newPosition);
        }
    }

    void GUIMovablePanel::StartMove()
    {
        m_isBeingMoved = true;

        m_moveStartingPosition = this->GetBounds().GetPosition();

        m_moveStartingMousePosition = GetNormallizedMousePosition(_<SDLDevice>().GetWindow());
    }

    void GUIMovablePanel::StopMove()
    {
        m_isBeingMoved = false;
    }

    RectF GUIMovablePanel::GetDraggableArea()
    {
        return this->GetBounds();
    }
}