//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Tile.hpp"
#include "ObjectsStack.hpp"

namespace Forradia::Theme0 {
    void Tile::Initialize() {
        m_objectsStack = std::make_shared<Forradia::Theme0::ObjectsStack>();
    }

    void Tile::SetGround(int groundHash) {
        m_ground = groundHash;
        this->SetForceRedraw(true);
    }

    void Tile::SetGround(StringView groundName) {
        this->SetGround(Hash(groundName));
    }
}