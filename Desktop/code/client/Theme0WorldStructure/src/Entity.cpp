/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Entity.hpp"

namespace Forradia::Theme0
{
    auto Entity::initialize() -> void
    {
        // Multiply movement speed by a random number between 0.5 and 2.
        m_movementSpeed *= (getRandomInt(3) + 1) / 2.0F;
    }
}
