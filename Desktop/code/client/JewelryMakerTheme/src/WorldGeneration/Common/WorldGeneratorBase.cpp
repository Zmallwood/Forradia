/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorBase.hpp"
#include <cmath>
#include "Properties/ThemeProperties.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "Player/Player.hpp"

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

    auto WorldGeneratorBase::getDistance(int xPos1, int yPos1, int xPos2, int yPos2) -> float
    {
        auto deltaX{static_cast<float>(xPos2 - xPos1)};
        auto deltaY{static_cast<float>(yPos2 - yPos1)};

        return std::sqrt(deltaX * deltaX + deltaY * deltaY);
    }
}
