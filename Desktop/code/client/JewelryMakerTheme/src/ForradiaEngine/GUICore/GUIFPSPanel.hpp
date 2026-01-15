/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIMovablePanel.hpp"

namespace ForradiaEngine
{
    class GUILabel;

    /**
     *  A panel that displays the FPS.
     */
    class GUIFPSPanel : public GUIMovablePanel
    {
      public:
        /**
         *  Constructor.
         */
        GUIFPSPanel()
            : GUIMovablePanel("FPSPanel", k_defaultBounds.x, k_defaultBounds.y,
                              k_defaultBounds.width, k_defaultBounds.height)
        {
            // Initialize this FPSPanel.
            this->initialize();
        }

      protected:
        /**
         *  Update tasks specific to the FPSPanel, called by the GUIComponent base class.
         */
        auto updateDerived() -> void override;

      private:
        /**
         *  Initializes this FPSPanel.
         */
        auto initialize() -> void;

        constexpr static RectF k_defaultBounds{0.92F, 0.02F, 0.07F, 0.04F};
        const RectF k_labelBounds{0.01F, 0.01F, 0.1F, 0.05F};
        std::shared_ptr<GUILabel> m_fpsTextLabel{};
    };
}
