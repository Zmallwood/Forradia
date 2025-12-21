/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIPanel.hpp"
#include "GUIScrollableArea.hpp"
#include "GUIWindow.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"

namespace Forradia::Theme0 {
    class Object;
    class GUIInventoryWindowArea;
    class GUIInventoryWindowPanel;
    class ContainedObjects;

    /**
     * Represents the inventory window.
     */
    class GUIInventoryWindow : public GUIWindow {
      public:
        static GUIInventoryWindow &Instance() {
            static GUIInventoryWindow instance(Singleton<Player>().GetObjectsInventoryRef());
            return instance;
        }
        // Delete copy/move
        GUIInventoryWindow(const GUIInventoryWindow &) = delete;
        GUIInventoryWindow &operator=(const GUIInventoryWindow &) = delete;

        /**
         * Constructor.
         */
        GUIInventoryWindow(ContainedObjects &containedObjects)
            : GUIWindow("GUIInventoryWindow", 0.5f, 0.2f, 0.2f, 0.5f, "Inventory") {
            this->Initialize(containedObjects);
        }

        std::shared_ptr<Object> *GetObjectPtrPtr(PointF position);

      private:
        auto Initialize(ContainedObjects &containedObjects) -> void;

        std::shared_ptr<GUIInventoryWindowArea> m_guiInventoryWindowArea;
    };

    class GUIInventoryWindowArea : public GUIScrollableArea {
      public:
        GUIInventoryWindowArea(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIScrollableArea("GUIInventoryWindowArea", 0.0F, 0.0F, 0.2F, 0.45F),
              m_parentWindow(parentWindow) {
            this->Initialize(parentWindow, containedObjects);
        }

        std::shared_ptr<Object> *GetObjectPtrPtr(PointF position);

      protected:
        auto UpdateDerived() -> void override;

        // auto GetBounds() const -> RectF override;

      private:
        auto Initialize(GUIWindow *parentWindow, ContainedObjects &containedObjects) -> void;

        GUIWindow *m_parentWindow{nullptr};
        std::shared_ptr<GUIInventoryWindowPanel> m_panel;
    };

    class GUIInventoryWindowPanel : public GUIPanel {
      public:
        GUIInventoryWindowPanel(GUIWindow *parentWindow, ContainedObjects &containedObjects)
            : GUIPanel("GUIInventoryWindowPanel", 0.0F, 0.0F, 0.2F, 1.0F),
              m_parentWindow(parentWindow), m_containedObjects(containedObjects) {
            this->Initialize();
        }

        std::shared_ptr<Object> *GetObjectPtrPtr(PointF position);

      protected:
        auto RenderDerived() const -> void override;

      private:
        auto Initialize() -> void;

        static constexpr float k_margin{0.005f};
        static constexpr float k_slotSize{0.04f};
        inline static const std::string k_slotImageName{"GUIInventoryWindowSlotBackground"};
        const int k_maxNumSlots{60};
        std::unordered_map<int, int> m_renderIDsSlotsBackground;
        std::unordered_map<int, int> m_renderIDsSlotsObject;
        GUIWindow *m_parentWindow{nullptr};
        ContainedObjects &m_containedObjects;
    };
}
