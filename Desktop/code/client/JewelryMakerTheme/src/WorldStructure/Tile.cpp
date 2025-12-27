/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Tile.hpp"
#include "ObjectsStack.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto Tile::initialize() -> void
    {
        m_objectsStack = std::make_shared<ForradiaEngine::JewelryMakerTheme::ObjectsStack>();
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
