/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIContainerWindow.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "ForradiaEngine/Common/Utilities/MouseUtilities.hpp"
    #include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"
    #include "ForradiaEngine/GUICore/GUIWindowTitleBar.hpp"
    #include "GUIContainerWindowArea.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIContainerWindow::initialize(ContainedObjects &containedObjects) -> void
    {
        m_guiContainerWindowArea = std::make_shared<GUIContainerWindowArea>(this, containedObjects);

        this->addChildComponent(m_guiContainerWindowArea);
    }

    std::shared_ptr<std::shared_ptr<Object>>
    GUIContainerWindow::getObjectPtrPtr(PointF position) const
    {
        return m_guiContainerWindowArea->getObjectPtrPtr(position);
    }
}
