/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
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
        /**
         *  Constructor.
         *
         *  @param parentWindow The parent window of the area.
         *  @param containedObjects The contained objects.
         */
        GUIContainerWindowArea(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIScrollableArea("GUIContainerWindowArea", k_defaultBounds.x, k_defaultBounds.y,
                                k_defaultBounds.width, k_defaultBounds.height),
              m_parentWindow(parentWindow)
        {
            this->initialize(parentWindow, containedObjects);
        }

        /**
         *  Gets the object pointer pointer at the given position in the area.
         *
         *  @param position The position to get the object pointer pointer at in the area.
         *  @return The object pointer pointer at the given position in the area.
         */
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