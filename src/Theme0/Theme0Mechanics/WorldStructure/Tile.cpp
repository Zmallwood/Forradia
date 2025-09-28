/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Tile.hpp"
#include "ObjectsStack.hpp"

namespace Forradia
{
    void Tile::Initialize()
    {
        m_objectsStack = std::make_shared<ObjectsStack>();
    }

    void Tile::SetGround(StringView groundName)
    {
        m_ground = Hash(groundName);
    }
}