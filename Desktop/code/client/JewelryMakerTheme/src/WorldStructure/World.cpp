/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "World.hpp"
#include "WorldArea.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto World::initialize(Size worldAreaSize, float worldScaling) -> void
    {
        auto worldArea{std::make_shared<WorldArea>(worldAreaSize, worldScaling)};

        m_worldAreas[0][0][0] = worldArea;

        auto worldAreaLowerFloors{std::make_shared<WorldArea>(worldAreaSize, worldScaling)};

        m_worldAreas[0][0][-1] = worldAreaLowerFloors;
    }

    auto World::getWorldArea(Point3 coordinate) -> std::shared_ptr<WorldArea>
    {
        return m_worldAreas[coordinate.x][coordinate.y][coordinate.z];
    }
}
