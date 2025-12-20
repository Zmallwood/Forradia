/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include "GUIWindow.hpp"

namespace Forradia {
    class GUILabel;
}

namespace Forradia::Theme0 {
    /**
     * Represents the player body window.
     */
    class GUIPlayerBodyWindow : public GUIWindow {
      public:
        /**
         * Constructor.
         */
        GUIPlayerBodyWindow()
            : GUIWindow("GUIPlayerBodyWindow", 0.2f, 0.2f, 0.2f, 0.5f, "Player body") {
            this->Initialize();
        }

      protected:
        /**
         * Initializes the player body window.
         */
        auto Initialize() -> void;

      private:
        auto SelectBodyPart(int type) -> void;

        auto UpdateBodyPartInfoLabels() -> void;

        int m_selectedBodyPart{0};
        std::shared_ptr<GUILabel> m_labelBodyPartName;
        std::shared_ptr<GUILabel> m_labelBodyPartStrength;
        std::shared_ptr<GUILabel> m_labelBodyPartEnergy;
        std::shared_ptr<GUILabel> m_labelBodyPartTemperature;
    };
}
