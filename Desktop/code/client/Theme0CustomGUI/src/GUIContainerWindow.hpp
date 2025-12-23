/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIPanel.hpp"
#include "GUIScrollableArea.hpp"
#include "GUIWindow.hpp"

namespace Forradia::Theme0
{
    class Object;
    class GUIContainerWindowArea;
    class GUIContainerWindowPanel;
    class ContainedObjects;

    /**
        Represents the inventory window.
     */
    class GUIContainerWindow : public GUIWindow
    {
      public:
        /**
            Constructor.
         */
        GUIContainerWindow(ContainedObjects &containedObjects)
            : GUIWindow("GUIContainerWindow", 0.5f, 0.2f, 0.2f, 0.5f, "Container")
        {
            this->Initialize(containedObjects);
        }

        std::shared_ptr<std::shared_ptr<Object>> GetObjectPtrPtr(PointF position) const;

      private:
        auto Initialize(ContainedObjects &containedObjects) -> void;

        std::shared_ptr<GUIContainerWindowArea> m_guiContainerWindowArea{};
    };

    class GUIContainerWindowArea : public GUIScrollableArea
    {
      public:
        GUIContainerWindowArea(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIScrollableArea("GUIContainerWindowArea", 0.0F, 0.0F, 0.2F, 0.45F),
              m_parentWindow(parentWindow)
        {
            this->Initialize(parentWindow, containedObjects);
        }

        std::shared_ptr<std::shared_ptr<Object>> GetObjectPtrPtr(PointF position) const;

      protected:
        auto UpdateDerived() -> void override;

      private:
        auto Initialize(GUIWindow *parentWindow, ContainedObjects &containedObjects) -> void;

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
            this->Initialize();
        }

        std::shared_ptr<std::shared_ptr<Object>> GetObjectPtrPtr(PointF position) const;

      protected:
        auto RenderDerived() const -> void override;

      private:
        auto Initialize() -> void;

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
