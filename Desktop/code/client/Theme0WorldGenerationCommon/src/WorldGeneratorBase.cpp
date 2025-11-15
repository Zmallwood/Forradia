//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorBase.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Theme0Properties.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorBase::Prepare()
    {
        // Get required world related properties.

        m_worldArea = _<Theme0::World>().GetCurrentWorldArea();

        m_worldAreaSize = m_worldArea->GetSize();

        m_worldScaling = _<Theme0::Theme0Properties>().GetWorldScaling();
    }

    float WorldGeneratorBase::GetDistance(int x1, int y1, int x2, int y2) const
    {
        // Calculate the distance between two points.

        auto dx{static_cast<float>(x2 - x1)};

        auto dy{static_cast<float>(y2 - y1)};

        // Return the distance.

        return std::sqrt(dx * dx + dy * dy);
    }
}