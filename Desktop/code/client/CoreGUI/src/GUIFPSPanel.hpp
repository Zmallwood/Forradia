/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIMovablePanel.hpp"

namespace Forradia {
class GUILabel;

/**
 * A panel that displays the FPS.
 */
class GUIFPSPanel : public GUIMovablePanel {
 public:
  /**
   * Constructor.
   */
  GUIFPSPanel() : GUIMovablePanel("FPSPanel", 0.92f, 0.02f, 0.07f, 0.04f) {
    // Initialize this FPSPanel.
    this->Initialize();
  }

 protected:
  /**
   * Update tasks specific to the FPSPanel, called by the GUIComponent base class.
   */
  void UpdateDerived() override;

 private:
  /**
   * Initializes this FPSPanel.
   */
  void Initialize();

  SharedPtr<GUILabel> m_fpsTextPanel;
};
}