//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia
{
    namespace Theme0
    {
        void WorldGenerator::ClearWithDirt() const
        {
            for (auto y = 0; y < m_size.height; y++)
            {
                for (auto x = 0; x < m_size.width; x++)
                {
                    auto tile{m_worldArea->GetTile(x, y)};

                    if (tile)
                    {
                        tile->SetGround("ground_dirt");
                    }
                }
            }
        }
    }
}