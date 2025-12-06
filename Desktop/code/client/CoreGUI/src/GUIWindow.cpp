//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIWindow.hpp"
#include "GUIWindowTitleBar.hpp"

namespace Forradia
{
    void GUIWindow::Initialize(StringView uniqueName, StringView windowTitle)
    {
        // Hide the window initially.

        this->SetVisible(false);

        // Create the window title bar.

        m_guiWindowTitleBar = std::make_shared<GUIWindowTitleBar>(uniqueName, *this, windowTitle);

        // Add the window title bar to the window.

        this->AddChildComponent(m_guiWindowTitleBar);
    }

    void GUIWindow::RenderDerived() const
    {
        // Call the GUIMovablePanel base class render derived method.

        GUIMovablePanel::RenderDerived();
    }

    RectF GUIWindow::GetDraggableArea() const
    {
        // Return the bounds of the window title bar as the draggable area.

        return m_guiWindowTitleBar->GetBounds();
    }
}