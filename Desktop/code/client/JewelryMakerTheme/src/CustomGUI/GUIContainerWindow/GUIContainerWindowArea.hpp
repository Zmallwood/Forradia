/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>
#include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"

namespace ForradiaEngine
{
    class GUIWindow;
}

namespace ForradiaEngine::JewelryMakerTheme
{
    class ContainedObjects;
    class GUIContainerWindowPanel;
    class Object;

    class GUIContainerWindowArea : public GUIScrollableArea
    {
      public:
        GUIContainerWindowArea(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIScrollableArea("GUIContainerWindowArea", k_defaultBounds.x, k_defaultBounds.y,
                                k_defaultBounds.width, k_defaultBounds.height),
              m_parentWindow(parentWindow)
        {
            this->initialize(parentWindow, containedObjects);
        }

        auto getObjectPtrPtr(PointF position) const -> std::shared_ptr<std::shared_ptr<Object>>;

      protected:
        auto updateDerived() -> void override;

      private:
        auto initialize(GUIWindow *parentWindow, ContainedObjects &containedObjects) -> void;

        constexpr static RectF k_defaultBounds{0.0F, 0.0F, 0.2F, 0.45F};
        GUIWindow *m_parentWindow{nullptr};
        std::shared_ptr<GUIContainerWindowPanel> m_panel{};
    };
}