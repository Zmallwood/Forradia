//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIEnergyStatisticsPanel.hpp"
#include "GUILabel.hpp"
#include "Energy/EnergyComputation.hpp"

namespace AAK
{
    namespace Forradia
    {
        void GUIEnergyStatisticsPanel::Initialize()
        {
            // Create the energy-per-tile text label.

            m_energyPerTileTextPanel =
                std::make_shared<GUILabel>("GUILabelEnergyPerTilePanel", 0.01f, 0.01f, 0.1f, 0.05f);

            // Add the energy-per-tile text label to this panel.

            this->AddChildComponent(m_energyPerTileTextPanel);
        }

        void GUIEnergyStatisticsPanel::UpdateDerived()
        {
            // Do the updating specific to the base class (GUIMovablePanel).

            GUIMovablePanel::UpdateDerived();

            // Get the  energy-per-tile.

            auto energyPerTile{
                _<Theme0::GameplayCore::EnergyComputation>().ComputeEnergyProductionPerTile()};

            // Set the text of the  energy-per-tile text label.

            m_energyPerTileTextPanel->SetText(fmt::format("Energy per tile: {}", energyPerTile));
        }
    }
}