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
        void WorldGenerator::GenerateLakes() const
        {
            auto numLakes{20 + GetRandomInt(5)};

            for (auto i = 0; i < numLakes; i++)
            {
                this->GenerateSingleLake(
                    0, 0, m_size.width, m_size.height,
                    2 + GetRandomInt(5));
            }
        }
    }
}