/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIWindow.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"

namespace Forradia
{
    void GUIWindow::Initialize()
    {
        SetVisible(false);
    }

    void GUIWindow::UpdateDerived()
    {
        GUIMovablePanel::UpdateDerived();

        m_guiWindowTitleBar.Update();

        auto mousePosition{GetNormalizedMousePosition()};

        auto bounds{GetBounds()};

        if (bounds.Contains(mousePosition))
        {
            if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenFiredDontPickResult())
            {
                _<MouseInput>().GetLeftMouseButtonRef().Reset();
            }
        }
    }

    void GUIWindow::RenderDerived() const
    {
        GUIMovablePanel::RenderDerived();

        m_guiWindowTitleBar.Render();
    }
}