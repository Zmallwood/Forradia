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
        // Initialize the objects stack.
        m_objectsStack = std::make_shared<Forradia::Theme0::ObjectsStack>();
    }

    void Tile::SetGround(int groundHash) {
        // Set the ground type provided as hash.
        m_ground = groundHash;

        // Force a redraw of the tile.
        this->SetForceRedraw(true);
    }

    void Tile::SetGround(StringView groundName) {
        // Set the ground type, provided by name, as hash.
        this->SetGround(Hash(groundName));
    }
}