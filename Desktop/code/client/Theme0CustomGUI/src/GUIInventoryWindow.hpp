/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
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

 protected:
  /**
   * Initializes the inventory window.
   */
  auto Initialize() -> void;

  /**
   * Does render logic that is specific to the inventory window.
   */
  auto RenderDerived() const -> void override;

 private:
  static constexpr float k_margin{0.005f};
  static constexpr float k_slotSize{0.04f};
  inline static const String k_slotImageName{"GUIInventoryWindowSlotBackground"};
  const int k_maxNumSlots{60};
  std::map<int, int> m_renderIDsSlotsBackground;
  std::map<int, int> m_renderIDsSlotsObject;
};
}
