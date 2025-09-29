/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIWindow.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"
#include "Core/Cursor/Cursor.hpp"

namespace Forradia
{
    void GUIWindow::Initialize()
    {
        SetVisible(false);
    }

    void GUIWindow::UpdateDerived()
    {
        GUIMovablePanel::UpdateDerived();

        auto mousePosition{GetNormalizedMousePosition()};

        auto draggableArea{GetDraggableArea()};

        if (draggableArea.Contains(mousePosition))
        {
            _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

            if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenFiredPickResult())
            {
                StartMoving();
            }
        }

        if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenReleasedDontPickResult())
        {
            StopMoving();
        }

        auto bounds{GetBounds()};

        if (bounds.Contains(mousePosition))
        {
            if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenFiredDontPickResult())
            {
                _<MouseInput>().GetLeftMouseButtonRef().Reset();
            }
        }

        if (GetIsBeingMoved())
        {
            auto moveStartPosition{GetMoveStartPosition()};

            auto moveStartMousePosition{GetMoveStartMousePosition()};

            auto currentMousePosition{GetNormalizedMousePosition()};

            auto newPosition{moveStartPosition + currentMousePosition - moveStartMousePosition};

            SetPosition(newPosition);
        }
    }

    void GUIWindow::RenderDerived() const
    {
        GUIMovablePanel::RenderDerived();

        m_guiWindowTitleBar.Render();
    }

    RectF GUIWindow::GetDraggableArea()
    {
        return m_guiWindowTitleBar.GetBounds();
    }
}