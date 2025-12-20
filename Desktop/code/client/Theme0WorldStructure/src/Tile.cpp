/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Tile.hpp"
#include "ObjectsStack.hpp"

namespace Forradia::Theme0 {
    auto Tile::Initialize() -> void {
        m_objectsStack = std::make_shared<Forradia::Theme0::ObjectsStack>();
    }

    auto Tile::SetGround(int groundHash) -> void {
        m_ground = groundHash;
        this->SetForceRedraw(true);
    }

    auto Tile::SetGround(std::string_view groundName) -> void {
        this->SetGround(Hash(groundName));
    }
}
