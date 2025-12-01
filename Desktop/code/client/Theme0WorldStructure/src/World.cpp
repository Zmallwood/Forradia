//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "World.hpp"
#include "WorldArea.hpp"

namespace AAK
{
    namespace Forradia::Theme0
    {
        void World::Initialize(Size worldAreaSize, float worldScaling)
        {
            // Create a new world area.

            m_currentWorldArea = std::make_shared<WorldArea>(worldAreaSize, worldScaling);
        }
    }
}