//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "Creature.hpp"

namespace Forradia::Theme0
{
    void Creature::Initialize()
    {
        // Multiply movement speed by a random number between 0.5 and 2.

        m_movementSpeed *= (GetRandomInt(3) + 1) / 2.0f;
    }
}