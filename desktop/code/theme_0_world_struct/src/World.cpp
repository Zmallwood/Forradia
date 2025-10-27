//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "World.hpp"

#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    void World::Initialize(Size w_area_sz,
                           float world_scaling)
    {
        m_currentWorldArea = std::make_shared<WorldArea>(
            w_area_sz, world_scaling);
    }
}