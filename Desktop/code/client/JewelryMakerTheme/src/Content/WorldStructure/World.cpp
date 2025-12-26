/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "World.hpp"
    #include "WorldArea.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto World::initialize(Size worldAreaSize, float worldScaling) -> void
    {
        auto worldArea{std::make_shared<WorldArea>(worldAreaSize, worldScaling)};

        m_worldAreas[0][0][0] = worldArea;
    }

    auto World::getCurrentWorldArea() -> std::shared_ptr<WorldArea>
    {
        return m_worldAreas[0][0][0];
    }
}
