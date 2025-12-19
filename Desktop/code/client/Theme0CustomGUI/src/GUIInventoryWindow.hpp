/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIPanel.hpp"
#include "GUIScrollableFrame.hpp"
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

  class GUIInventoryWindowFrame : public GUIScrollableFrame {
   public:
    GUIInventoryWindowFrame(GUIWindow *parentWindow)
        : GUIScrollableFrame("GUIInventoryWindowFrame", 0.0F, 0.0F, 0.2F, 0.3F),
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
        : GUIPanel("GUIInventoryWindowPanel", 0.0F, 0.0F, 0.2F, 0.5F),
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
    std::map<int, int> m_renderIDsSlotsBackground;
    std::map<int, int> m_renderIDsSlotsObject;
    GUIWindow *m_parentWindow{nullptr};
  };
}
