/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"
    #include <unordered_map>
// clang-format on

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
            : GUIScrollableArea("GUIContainerWindowArea", 0.0F, 0.0F, 0.2F, 0.45F),
              m_parentWindow(parentWindow)
        {
            this->initialize(parentWindow, containedObjects);
        }

        auto getObjectPtrPtr(PointF position) const -> std::shared_ptr<std::shared_ptr<Object>>;

      protected:
        auto updateDerived() -> void override;

      private:
        auto initialize(GUIWindow *parentWindow, ContainedObjects &containedObjects) -> void;

        GUIWindow *m_parentWindow{nullptr};
        std::shared_ptr<GUIContainerWindowPanel> m_panel{};
    };
}