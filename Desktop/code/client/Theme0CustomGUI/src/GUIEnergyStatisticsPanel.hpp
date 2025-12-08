//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUILabel;

    ///
    /// A panel that displays the FPS.
    ///
    class GUIEnergyStatisticsPanel : public GUIMovablePanel
    {
      public:
        ///
        /// Constructor.
        ///
        GUIEnergyStatisticsPanel()
            : GUIMovablePanel("EnergyStatisticsPanel", 0.02f, 0.14f, 0.15f, 0.04f)
        {
            // Initialize this FPSPanel.

            this->Initialize();
        }

      protected:
        ///
        /// Update tasks specific to the FPSPanel, called by the GUIComponent base class.
        ///
        void UpdateDerived() override;

      private:
        ///
        /// Initializes this FPSPanel.
        ///
        void Initialize();

        SharedPtr<GUILabel> m_energyPerTileTextPanel; ///< The text label that displays the FPS.
    };
}