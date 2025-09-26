/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Player.hpp"

namespace Forradia
{
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