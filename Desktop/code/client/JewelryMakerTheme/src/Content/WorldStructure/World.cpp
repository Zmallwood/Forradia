/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "World.hpp"
    #include "WorldArea.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    auto World::initialize(Size worldAreaSize, float worldScaling) -> void
    {
        m_currentWorldArea = std::make_shared<WorldArea>(worldAreaSize, worldScaling);
    }
}
