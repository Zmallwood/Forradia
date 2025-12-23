/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Player.hpp"
#include "NumbersUtilities.hpp"
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

        if (now >= m_ticksLastMovement + InvertSpeed(m_movementSpeed) &&
            m_playerMoveDirection != PlayerMoveDirections::None)
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

            case PlayerMoveDirections::NorthEast:
                this->MoveNorth();
                this->MoveEast();
                break;

            case PlayerMoveDirections::SouthEast:
                this->MoveSouth();
                this->MoveEast();
                break;

            case PlayerMoveDirections::SouthWest:
                this->MoveSouth();
                this->MoveWest();
                break;

            case PlayerMoveDirections::NorthWest:
                this->MoveNorth();
                this->MoveWest();
                break;

            case PlayerMoveDirections::None:
                break;
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

    auto Player::StartMovingNorthWest() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::NorthWest;
    }

    auto Player::StartMovingNorthEast() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::NorthEast;
    }

    auto Player::StartMovingSouthWest() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::SouthWest;
    }

    auto Player::StartMovingSouthEast() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::SouthEast;
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
            m_playerMoveDirection = PlayerMoveDirections::North;
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
            m_playerActions.push_back({PlayerActionTypes::MoveEast, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::East;
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
            m_playerActions.push_back({PlayerActionTypes::MoveSouth, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::South;
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
            m_playerActions.push_back({PlayerActionTypes::MoveWest, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::West;
        }
    }

    auto Player::MoveNorthEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y - 1};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorthEast, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::NorthEast;
        }
    }

    auto Player::MoveSouthEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y + 1};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveSouthEast, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::SouthEast;
        }
    }

    auto Player::MoveSouthWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y + 1};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveSouthWest, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::SouthWest;
        }
    }

    auto Player::MoveNorthWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y - 1};

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater"))
        {
            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorthWest, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::NorthWest;
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

    PointF Player::GetSmoothPosition() const
    {
        auto dx{0.0F};
        auto dy{0.0F};

        auto now{GetTicks()};

        auto elapsedTime{now - m_ticksLastMovement};
        auto timeForOneStep{static_cast<int>(InvertSpeed(m_movementSpeed))};

        auto moveProgress{static_cast<float>(elapsedTime) / timeForOneStep};

        if (moveProgress > 1.0F)
        {
            moveProgress = -1.0F;
        }

        switch (m_playerMoveDirection)
        {
        case PlayerMoveDirections::North:
            dy = -moveProgress;
            break;

        case PlayerMoveDirections::East:
            dx = moveProgress;
            break;

        case PlayerMoveDirections::South:
            dy = moveProgress;
            break;

        case PlayerMoveDirections::West:
            dx = -moveProgress;
            break;

        case PlayerMoveDirections::NorthEast:
            dx = moveProgress;
            dy = -moveProgress;
            break;

        case PlayerMoveDirections::SouthEast:
            dx = moveProgress;
            dy = moveProgress;
            break;

        case PlayerMoveDirections::SouthWest:
            dx = -moveProgress;
            dy = moveProgress;
            break;

        case PlayerMoveDirections::NorthWest:
            dx = -moveProgress;
            dy = -moveProgress;
            break;

        case PlayerMoveDirections::None:
            break;
        }

        auto position{m_position};

        return {position.x + dx, position.y + dy};
    }
}
