/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
  /**
   * The root GUI class which is created for every scene.
   */
  class GUI : public GUIComponent {
   public:
    /**
     * Constructor.
     */
    GUI() : GUIComponent(0.0F, 0.0F, 1.0F, 1.0F) {
    }

    auto MouseHoveringGUI() const -> bool override;
  };
}
