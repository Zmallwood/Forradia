/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIPanel.hpp"
#include "GUIScrollableArea.hpp"
#include "GUIWindow.hpp"

namespace Forradia::Theme0 {
  /**
   * Represents the inventory window.
   */
  class GUIInventoryWindow : public GUIWindow {
   public:
    /**
     * Constructor.
     */
    GUIInventoryWindow() : GUIWindow("GUIInventoryWindow", 0.5f, 0.2f, 0.2f, 0.5f, "Inventory") {
      this->Initialize();
    }

   private:
    auto Initialize() -> void;
  };

  class GUIInventoryWindowArea : public GUIScrollableArea {
   public:
    GUIInventoryWindowArea(GUIWindow *parentWindow)
        : GUIScrollableArea("GUIInventoryWindowArea", 0.0F, 0.0F, 0.2F, 0.45F),
          m_parentWindow(parentWindow) {
      this->Initialize(parentWindow);
    }

   protected:
    auto UpdateDerived() -> void override;

    auto GetBounds() const -> RectF override;

   private:
    auto Initialize(GUIWindow *parentWindow) -> void;

    GUIWindow *m_parentWindow{nullptr};
  };

  class GUIInventoryWindowPanel : public GUIPanel {
   public:
    GUIInventoryWindowPanel(GUIWindow *parentWindow)
        : GUIPanel("GUIInventoryWindowPanel", 0.0F, 0.0F, 0.2F, 1.0F),
          m_parentWindow(parentWindow) {
      this->Initialize();
    }

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
  };
}
