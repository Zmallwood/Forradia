/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
    #include <unordered_map>
// clang-format on

namespace ForradiaEngine
{
    class GUIWindow;
}

namespace ForradiaEngine::JewelryMakerTheme
{
    class ContainedObjects;
    class Object;

    class GUIContainerWindowPanel : public GUIPanel
    {
      public:
        GUIContainerWindowPanel(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIPanel("GUIContainerWindowPanel", k_defaultBounds.x, k_defaultBounds.y,
                       k_defaultBounds.width, k_defaultBounds.height),
              m_parentWindow(parentWindow), m_containedObjects(containedObjects)
        {
            this->initialize();
        }

        auto getObjectPtrPtr(PointF position) const -> std::shared_ptr<std::shared_ptr<Object>>;

      protected:
        auto renderDerived() const -> void override;

      private:
        auto initialize() -> void;
        constexpr static RectF k_defaultBounds{0.0F, 0.0F, 0.2F, 1.0F};
        static constexpr float k_margin{0.005F};
        static constexpr float k_slotSize{0.04F};
        inline static const std::string k_slotImageName{"GUIContainerWindowSlotBackground"};
        const int k_maxNumSlots{60};
        std::unordered_map<int, int> m_renderIDsSlotsBackground{};
        std::unordered_map<int, int> m_renderIDsSlotsObject{};
        GUIWindow *m_parentWindow{nullptr};
        ContainedObjects &m_containedObjects;
    };
}