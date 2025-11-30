//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Tile.hpp"

#include "ObjectsStack.hpp"

namespace AAK
{
    namespace Forradia::Theme0
    {
        void Tile::Initialize()
        {
            // Initialize the objects stack.

            m_objectsStack = std::make_shared<Forradia::Theme0::ObjectsStack>();
        }

        void Tile::SetGround(int groundHash)
        {
            // Set the ground type provided as hash.

            m_ground = groundHash;
        }

        void Tile::SetGround(StringView groundName)
        {
            // Set the ground type, provided by name, as hash.

            m_ground = Hash(groundName);
        }
    }
}