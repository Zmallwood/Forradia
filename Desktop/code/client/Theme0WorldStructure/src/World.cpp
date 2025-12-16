//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
    void World::Initialize(Size worldAreaSize, float worldScaling) {
        // Create a new world area.

        m_currentWorldArea = std::make_shared<WorldArea>(worldAreaSize, worldScaling);
    }
}