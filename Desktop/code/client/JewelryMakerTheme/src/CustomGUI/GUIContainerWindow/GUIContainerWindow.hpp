/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>
#include "ForradiaEngine/GUICore/GUIPanel.hpp"
#include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"
#include "ForradiaEngine/GUICore/GUIWindow.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class Object;
    class GUIContainerWindowArea;
    class ContainedObjects;

    /**
     *  Represents the inventory window.
     */
    class GUIContainerWindow : public GUIWindow
    {
      public:
        /**
         *  Constructor.
         */
        GUIContainerWindow(ContainedObjects &containedObjects)
            : GUIWindow("GUIContainerWindow", k_defaultBounds.x, k_defaultBounds.y,
                        k_defaultBounds.width, k_defaultBounds.height, "Container")
        {
            this->initialize(containedObjects);
        }

        /**
         *  Gets the object pointer pointer at the given position in the window.
         *
         *  @param position The position to get the object pointer pointer at in the window.
         *  @return The object pointer pointer at the given position in the window.
         */
        auto getObjectPtrPtr(PointF position) const -> std::shared_ptr<std::shared_ptr<Object>>;

      private:
        auto initialize(ContainedObjects &containedObjects) -> void;

        constexpr static RectF k_defaultBounds{0.5F, 0.2F, 0.2F, 0.5F};
        std::shared_ptr<GUIContainerWindowArea> m_guiContainerWindowArea{};
    };
}
