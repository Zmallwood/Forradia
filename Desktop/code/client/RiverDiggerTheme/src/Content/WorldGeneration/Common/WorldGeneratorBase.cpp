/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorBase.hpp"
#include "Content/Properties/Theme0Properties.hpp"
#include "Content/WorldStructure/World.hpp"
#include "Content/WorldStructure/WorldArea.hpp"

namespace Forradia::Theme0
{
    auto WorldGeneratorBase::prepare() -> void
    {
        m_worldArea = Theme0::World::instance().getCurrentWorldArea();
        m_worldAreaSize = m_worldArea->getSize();
        m_worldScaling = Theme0::Theme0Properties::getWorldScaling();
    }

    auto WorldGeneratorBase::getDistance(int x1, int y1, int x2, int y2) -> float
    {
        auto dx{static_cast<float>(x2 - x1)};
        auto dy{static_cast<float>(y2 - y1)};

        return std::sqrt(dx * dx + dy * dy);
    }
}
