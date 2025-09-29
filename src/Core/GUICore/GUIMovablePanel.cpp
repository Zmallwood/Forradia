/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIMovablePanel.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"

namespace Forradia
{
    void GUIMovablePanel::UpdateDerived()
    {
    }

    void GUIMovablePanel::StartMoving()
    {
        m_isBeingMoved = true;

        m_moveStartPosition = GetBounds().GetPosition();
        m_moveStartMousePosition = GetNormalizedMousePosition();
    }

    void GUIMovablePanel::StopMoving()
    {
        m_isBeingMoved = false;
    }

    RectF GUIMovablePanel::GetDraggableArea()
    {
        return GetBounds();
    }
}