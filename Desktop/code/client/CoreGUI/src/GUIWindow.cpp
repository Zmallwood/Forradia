/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIWindow.hpp"
#include "GUIWindowTitleBar.hpp"

namespace Forradia {
    auto GUIWindow::Initialize(std::string_view uniqueName, std::string_view windowTitle) -> void {
        this->SetVisible(false);
        m_guiWindowTitleBar = std::make_shared<GUIWindowTitleBar>(uniqueName, *this, windowTitle);
        this->AddChildComponent(m_guiWindowTitleBar);
        s_positionOffset += 0.05F;
    }

    auto GUIWindow::RenderDerived() const -> void {
        GUIMovablePanel::RenderDerived();
    }

    auto GUIWindow::GetDraggableArea() const -> RectF {
        // Return the bounds of the window title bar as the draggable area.
        return m_guiWindowTitleBar->GetBounds();
    }
}
