/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Tile.hpp"
    #include "ObjectsStack.hpp"
// clang-format on

namespace Forradia::Theme0
{
    auto Tile::initialize() -> void
    {
        m_objectsStack = std::make_shared<Forradia::Theme0::ObjectsStack>();
    }

    auto Tile::setGround(int groundHash) -> void
    {
        m_ground = groundHash;

        this->setForceRedraw(true);
    }

    auto Tile::setGround(std::string_view groundName) -> void
    {
        this->setGround(hash(groundName));
    }
}
