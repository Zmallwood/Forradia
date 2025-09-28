/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Player.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"

namespace Forradia
{
    void Player::Initialize()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        m_position = {size.width / 2, size.height / 2};

        while (worldArea->GetTile(m_position)->GetGround() == Hash("GroundWater"))
        {
            m_position = {RandomInt(size.width), RandomInt(size.height)};
        }
    }

    void Player::MoveNorth()
    {
        m_position.y -= 1;
    }

    void Player::MoveEast()
    {
        m_position.x += 1;
    }

    void Player::MoveSouth()
    {
        m_position.y += 1;
    }

    void Player::MoveWest()
    {
        m_position.x -= 1;
    }
}