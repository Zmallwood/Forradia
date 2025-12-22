/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorBase.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    auto WorldGeneratorBase::Prepare() -> void
    {
        m_worldArea = Theme0::World::Instance().GetCurrentWorldArea();
        m_worldAreaSize = m_worldArea->GetSize();
        m_worldScaling = Theme0::Theme0Properties::Instance().GetWorldScaling();
    }

    auto WorldGeneratorBase::GetDistance(int x1, int y1, int x2, int y2) const -> float
    {
        auto dx{static_cast<float>(x2 - x1)};
        auto dy{static_cast<float>(y2 - y1)};

        return std::sqrt(dx * dx + dy * dy);
    }
}
