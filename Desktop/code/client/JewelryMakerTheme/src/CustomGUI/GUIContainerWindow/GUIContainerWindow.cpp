/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIContainerWindow.hpp"
#include "Essentials/Player/Player.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"
#include "ForradiaEngine/GUICore/GUIWindowTitleBar.hpp"
#include "GUIContainerWindowArea.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIContainerWindow::initialize(ContainedObjects &containedObjects) -> void
    {
        m_guiContainerWindowArea = std::make_shared<GUIContainerWindowArea>(this, containedObjects);

        this->addChildComponent(m_guiContainerWindowArea);
    }

    auto GUIContainerWindow::getObjectPtrPtr(PointF position) const
        -> std::shared_ptr<std::shared_ptr<Object>>
    {
        return m_guiContainerWindowArea->getObjectPtrPtr(position);
    }
}
