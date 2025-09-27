/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Creature.hpp"

namespace Forradia
{
    Creature::Creature(StringView typeName)
        : m_type{Hash(typeName)}
    {
        m_movementSpeed *= (RandomInt(3) + 1) / 2.0f;
    }
}