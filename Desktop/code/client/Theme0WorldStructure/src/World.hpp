//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class WorldArea;

    ///
    /// The world in the game.
    ///
    class World
    {
      public:
        ///
        /// Initializes the world.
        ///
        /// @param w_area_sz The size of the world area.
        /// @param world_scaling The scaling of the world.
        ///
        void Initialize(Size worldAreaSize, float worldScaling);

        ///
        /// Gets the current world area.
        ///
        /// @return The current world area.
        ///
        auto GetCurrentWorldArea() const
        {
            return m_currentWorldArea;
        }

      private:
        SharedPtr<WorldArea> m_currentWorldArea; ///< The current world area.
    };
}