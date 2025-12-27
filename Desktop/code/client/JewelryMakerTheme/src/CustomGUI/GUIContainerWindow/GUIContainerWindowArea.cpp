/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIContainerWindowArea.hpp"

#include "WorldStructure/Object.hpp"
#include "GUIContainerWindowPanel.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIContainerWindowArea::initialize(GUIWindow *parentWindow,
                                            ContainedObjects &containedObjects) -> void
    {
        m_panel = std::make_shared<GUIContainerWindowPanel>(parentWindow, containedObjects);

        this->addChildComponent(m_panel);
    }

    auto GUIContainerWindowArea::getObjectPtrPtr(PointF position) const
        -> std::shared_ptr<std::shared_ptr<Object>>
    {
        return m_panel->getObjectPtrPtr(position);
    }

    auto GUIContainerWindowArea::updateDerived() -> void
    {
        GUIScrollableArea::updateDerived();
    }
}