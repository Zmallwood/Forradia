/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIComponent.hpp"

namespace Forradia::Theme0 {
/**
 * Represents the system menu.
 */
class GUISystemMenu : public GUIComponent {
 public:
  /**
   * Constructor.
   */
  GUISystemMenu() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f) {
    this->Initialize();
  }

 protected:
  /**
   * Initializes the system menu.
   */
  void Initialize();

  /**
   * Does update logic that is specific to the system menu.
   */
  virtual void UpdateDerived() override;

  /**
   * Does render logic that is specific to the system menu.
   */
  virtual void RenderDerived() const override;

 private:
  const int k_renderIDBackgroundColor{Hash("GUISystemMenuBackgroundColor")};
};
}