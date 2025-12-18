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
  GUIFPSPanel() : GUIMovablePanel("FPSPanel", 0.92F, 0.02F, 0.07F, 0.04F) {
    // Initialize this FPSPanel.
    this->Initialize();
  }

 protected:
  /**
   * Update tasks specific to the FPSPanel, called by the GUIComponent base class.
   */
  auto UpdateDerived() -> void override;

 private:
  /**
   * Initializes this FPSPanel.
   */
  auto Initialize() -> void;

  SharedPtr<GUILabel> m_fpsTextPanel;
};
}
