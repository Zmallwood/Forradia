/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIWindow.hpp"

namespace Forradia::Theme0 {
    class GUIEquipmentWindow : public GUIWindow {
      public:
        /**
         * Constructor.
         */
        GUIEquipmentWindow()
            : GUIWindow("GUIEquipmentWindow", 0.2f, 0.2f, 0.2f, 0.5f, "Equipment") {
            this->Initialize();
        }

      protected:
        /**
         * Initializes the player body window.
         */
        auto Initialize() -> void;

      private:
    };
}
