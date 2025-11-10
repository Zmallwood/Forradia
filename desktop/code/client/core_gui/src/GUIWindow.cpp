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
        this->SetVisible(false);

        m_guiWindowTitleBar = std::make_shared<GUIWindowTitleBar>(uniqueName, *this, windowTitle);

        this->AddChildComponent(m_guiWindowTitleBar);
    }

    void GUIWindow::RenderDerived() const
    {
        GUIMovablePanel::RenderDerived();
    }

    RectF GUIWindow::GetDraggableArea()
    {
        return m_guiWindowTitleBar->GetBounds();
    }
}