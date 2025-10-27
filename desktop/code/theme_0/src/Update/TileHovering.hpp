//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
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