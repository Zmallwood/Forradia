/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIWindow.hpp"
    #include "GUIWindowTitleBar.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto GUIWindow::initialize(std::string_view uniqueName, std::string_view windowTitle) -> void
    {
        this->setVisible(false);

        m_guiWindowTitleBar = std::make_shared<GUIWindowTitleBar>(uniqueName, *this, windowTitle);
        this->addChildComponent(m_guiWindowTitleBar);

        s_positionOffset += k_positionOffsetChange;
    }

    auto GUIWindow::renderDerived() const -> void
    {
        GUIMovablePanel::renderDerived();
    }

    auto GUIWindow::getDraggableArea() const -> RectF
    {
        // Return the bounds of the window title bar as the draggable area.
        return m_guiWindowTitleBar->getBounds();
    }
}
