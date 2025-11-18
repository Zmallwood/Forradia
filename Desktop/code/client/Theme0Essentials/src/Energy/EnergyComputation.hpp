//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0::GameplayCore
{
    ///
    /// Does computations related to energy for the player.
    ///
    class EnergyComputation
    {
      public:
        ///
        /// Computes the energy production per tile.
        ///
        /// @return The energy production per tile.
        ///
        float ComputeEnergyProductionPerTile();
    };
}