/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
    #include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"
    #include "ForradiaEngine/GUICore/GUIWindow.hpp"
    #include <unordered_map>
// clang-format on

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
            : GUIWindow("GUIContainerWindow", 0.5f, 0.2f, 0.2f, 0.5f, "Container")
        {
            this->initialize(containedObjects);
        }

        auto getObjectPtrPtr(PointF position) const -> std::shared_ptr<std::shared_ptr<Object>>;

      private:
        auto initialize(ContainedObjects &containedObjects) -> void;

        std::shared_ptr<GUIContainerWindowArea> m_guiContainerWindowArea{};
    };
}
