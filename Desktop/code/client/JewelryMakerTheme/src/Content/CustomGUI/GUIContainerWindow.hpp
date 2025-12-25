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
    class GUIContainerWindowPanel;
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

    class GUIContainerWindowArea : public GUIScrollableArea
    {
      public:
        GUIContainerWindowArea(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIScrollableArea("GUIContainerWindowArea", 0.0F, 0.0F, 0.2F, 0.45F),
              m_parentWindow(parentWindow)
        {
            this->initialize(parentWindow, containedObjects);
        }

        std::shared_ptr<std::shared_ptr<Object>> getObjectPtrPtr(PointF position) const;

      protected:
        auto updateDerived() -> void override;

      private:
        auto initialize(GUIWindow *parentWindow, ContainedObjects &containedObjects) -> void;

        GUIWindow *m_parentWindow{nullptr};
        std::shared_ptr<GUIContainerWindowPanel> m_panel{};
    };

    class GUIContainerWindowPanel : public GUIPanel
    {
      public:
        GUIContainerWindowPanel(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIPanel("GUIContainerWindowPanel", 0.0F, 0.0F, 0.2F, 1.0F),
              m_parentWindow(parentWindow), m_containedObjects(containedObjects)
        {
            this->initialize();
        }

        std::shared_ptr<std::shared_ptr<Object>> getObjectPtrPtr(PointF position) const;

      protected:
        auto renderDerived() const -> void override;

      private:
        auto initialize() -> void;

        static constexpr float k_margin{0.005f};
        static constexpr float k_slotSize{0.04f};
        inline static const std::string k_slotImageName{"GUIContainerWindowSlotBackground"};
        const int k_maxNumSlots{60};
        std::unordered_map<int, int> m_renderIDsSlotsBackground{};
        std::unordered_map<int, int> m_renderIDsSlotsObject{};
        GUIWindow *m_parentWindow{nullptr};
        ContainedObjects &m_containedObjects;
    };
}
