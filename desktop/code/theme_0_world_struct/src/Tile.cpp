//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Tile.hpp"

#include "ObjectsStack.hpp"

namespace Forradia
{
    namespace Theme0
    {
        void Tile::Initialize()
        {
            m_objectsStack = std::make_shared<
                Forradia::Theme0::ObjectsStack>();
        }

        void Tile::SetGround(StringView ground_name)
        {
            m_ground = Hash(ground_name);
        }
    }
}