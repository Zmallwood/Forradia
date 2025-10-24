//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Common.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void UpdateKeyboardActions();

            void UpdateMouseActions();

            void UpdateKeyboardMovement();

            void UpdateMouseMovement();

            void UpdateCreaturesMovement();

            void UpdateNPCs();

            class TileHovering
            {
              public:
                void Update();

                auto GetHoveredCoordinate() const
                {
                    return m_hoveredCoordinate;
                }

              private:
                Point m_hoveredCoordinate{-1, -1};
            };
        }
    }
}