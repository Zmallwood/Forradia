/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Player.hpp"
#include "NumbersUtilities.hpp"
#include "ObjectsStack.hpp"
#include "PlayerObjectsInventory.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    auto Player::Initialize() -> void
    {
        m_playerObjectsInventory = std::make_shared<PlayerObjectsInventory>();

        this->MoveToSuitablePosition();
    }

    auto Player::MoveToSuitablePosition() -> void
    {
        auto worldArea{World::Instance().GetCurrentWorldArea()};
        auto size{worldArea->GetSize()};

        m_position = {size.width / 2, size.height / 2};

        while (worldArea->GetTile(m_position)->GetGround() == Hash("GroundWater"))
        {
            m_position = {GetRandomInt(size.width), GetRandomInt(size.height)};
        }
    }

    auto Player::Update() -> void
    {
        auto now{GetTicks()};

        if (now >= m_ticksLastMovement + InvertSpeed(m_movementSpeed))
        {
            switch (m_playerMoveDirection)
            {
            case PlayerMoveDirections::North:
                this->MoveNorth();
                break;

            case PlayerMoveDirections::East:
                this->MoveEast();
                break;

            case PlayerMoveDirections::South:
                this->MoveSouth();
                break;

            case PlayerMoveDirections::West:
                this->MoveWest();
                break;

            case PlayerMoveDirections::None:
            }

            m_ticksLastMovement = now;
        }
    }

    auto Player::StartMovingNorth() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::North;
    }

    auto Player::StartMovingEast() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::East;
    }

    auto Player::StartMovingSouth() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::South;
    }

    auto Player::StartMovingWest() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::West;
    }

    auto Player::StopMoving() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::None;
    }

    auto Player::MoveNorth() -> void
    {
        auto newX{m_position.x};
        auto newY{m_position.y - 1};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
        }
    }

    auto Player::MoveEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
        }
    }

    auto Player::MoveSouth() -> void
    {
        auto newX{m_position.x};
        auto newY{m_position.y + 1};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
        }
    }

    auto Player::MoveWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
        }
    }

    auto Player::AddExperience(int experience) -> void
    {
        m_experience += experience;
    }

    auto Player::AddPlayerAction(PlayerActionTypes playerAction,
                                 std::string_view actionFirstArgument, Point actionSecondArgument)
        -> void
    {
        m_playerActions.push_back(std::tuple<PlayerActionTypes, std::string, Point>{
            playerAction, actionFirstArgument, actionSecondArgument});
    }
}
