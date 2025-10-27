//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Creature.hpp"

namespace Forradia::Theme0
{
    void Creature::Initialize()
    {
        m_movementSpeed *= (GetRandomInt(3) + 1) / 2.0f;
    }
}