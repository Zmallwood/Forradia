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
        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        auto dragArea{this->GetDragArea()};

        if (dragArea.Contains(mousePosition))
        {
            _<Cursor>().SetCursorStyle(
                CursorStyles::HoveringClickableGUI);

            if (_<MouseInput>()
                    .GetLeftMouseButtonRef()
                    .HasBeenFiredPickResult())
            {
                this->StartMove();
            }
        }

        if (_<MouseInput>()
                .GetLeftMouseButtonRef()
                .HasBeenReleased())
        {
            this->StopMove();
        }

        auto bounds{GetBounds()};

        if (bounds.Contains(mousePosition))
        {
            if (_<MouseInput>()
                    .GetLeftMouseButtonRef()
                    .HasBeenFired())
            {
                _<MouseInput>()
                    .GetLeftMouseButtonRef()
                    .Reset();
            }
        }
        if (GetIsBeingMoved())
        {
            auto currentMousePosition{
                GetNormallizedMousePosition(
                    _<SDLDevice>().GetWindow())};

            auto newPosition{
                GetMoveStartingPosition() +
                currentMousePosition -
                GetMoveStartingMousePosition()};

            this->SetPosition(newPosition);
        }
    }

    void GUIMovablePanel::StartMove()
    {
        m_isBeingMoved = true;

        m_moveStartingPosition =
            this->GetBounds().GetPosition();

        m_moveStartingMousePosition =
            GetNormallizedMousePosition(
                _<SDLDevice>().GetWindow());
    }

    void GUIMovablePanel::StopMove()
    {
        m_isBeingMoved = false;
    }

    RectF GUIMovablePanel::GetDragArea()
    {
        return this->GetBounds();
    }
}