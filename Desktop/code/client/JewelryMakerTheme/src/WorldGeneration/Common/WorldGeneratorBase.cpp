/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorBase.hpp"

#include "Properties/ThemeProperties.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "Essentials/Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorBase::prepare() -> void
    {
        m_worldArea = JewelryMakerTheme::World::instance().getWorldArea(
            Player::instance().getWorldAreaCoordinate());
        m_worldAreaSize = m_worldArea->getSize();
        m_worldScaling = JewelryMakerTheme::ThemeProperties::getWorldScaling();

        m_worldAreaLowerFloors = JewelryMakerTheme::World::instance().getWorldArea(
            Player::instance().getWorldAreaCoordinate().offset(Point3{0, 0, -1}));
        m_worldAreaLowerFloorsSize = m_worldAreaLowerFloors->getSize();
        m_worldScalingLowerFloors = JewelryMakerTheme::ThemeProperties::getWorldScaling();
    }

    auto WorldGeneratorBase::getDistance(int x1, int y1, int x2, int y2) -> float
    {
        auto dx{static_cast<float>(x2 - x1)};
        auto dy{static_cast<float>(y2 - y1)};

        return std::sqrt(dx * dx + dy * dy);
    }
}
