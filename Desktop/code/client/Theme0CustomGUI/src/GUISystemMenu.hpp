/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "GUIComponent.hpp"

namespace Forradia::Theme0 {
class GUISystemMenu : public GUIComponent {
 public:
  GUISystemMenu() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f) {
    this->Initialize();
  }

 protected:
  void Initialize();

  virtual void UpdateDerived() override;

  virtual void RenderDerived() const override;

 private:
  const int k_renderIDBackgroundColor{Hash("GUISystemMenuBackgroundColor")};
};
}