/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Player.hpp"
#include "Common/Utilities/NumbersUtilities.hpp"
#include "Object.hpp"
#include "Content/Properties/ObjectIndex.hpp"
#include "ObjectsStack.hpp"
#include "PlayerObjectsInventory.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    auto Player::initialize() -> void
    {
        m_playerObjectsInventory = std::make_shared<PlayerObjectsInventory>();

        this->moveToSuitablePosition();
    }

    auto Player::moveToSuitablePosition() -> void
    {
        auto worldArea{World::instance().getCurrentWorldArea()};
        auto size{worldArea->getSize()};

        m_position = {size.width / 2, size.height / 2};

        while (worldArea->getTile(m_position)->getGround() == hash("GroundWater"))
        {
            m_position = {getRandomInt(size.width), getRandomInt(size.height)};
        }
    }

    auto Player::update() -> void
    {
        auto now{getTicks()};

        if (now >= m_ticksLastMovement + invertSpeed(m_movementSpeed) &&
            m_playerMoveDirection != PlayerMoveDirections::None)
        {
            switch (m_playerMoveDirection)
            {
            case PlayerMoveDirections::North:
                this->moveNorth();
                break;

            case PlayerMoveDirections::East:
                this->moveEast();
                break;

            case PlayerMoveDirections::South:
                this->moveSouth();
                break;

            case PlayerMoveDirections::West:
                this->moveWest();
                break;

            case PlayerMoveDirections::NorthEast:
                this->moveNorth();
                this->moveEast();
                break;

            case PlayerMoveDirections::SouthEast:
                this->moveSouth();
                this->moveEast();
                break;

            case PlayerMoveDirections::SouthWest:
                this->moveSouth();
                this->moveWest();
                break;

            case PlayerMoveDirections::NorthWest:
                this->moveNorth();
                this->moveWest();
                break;

            case PlayerMoveDirections::None:
                break;
            }

            m_ticksLastMovement = now;

            if (m_position == m_destination)
            {
                m_destination = {-1, -1};
                m_playerMoveDirection = PlayerMoveDirections::None;
            }
        }
    }

    auto Player::startMovingNorth() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::North;
    }

    auto Player::startMovingEast() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::East;
    }

    auto Player::startMovingSouth() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::South;
    }

    auto Player::startMovingWest() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::West;
    }

    auto Player::startMovingNorthWest() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::NorthWest;
    }

    auto Player::startMovingNorthEast() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::NorthEast;
    }

    auto Player::startMovingSouthWest() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::SouthWest;
    }

    auto Player::startMovingSouthEast() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::SouthEast;
    }

    auto Player::stopMoving() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::None;
    }

    auto Player::moveNorth() -> void
    {
        auto newX{m_position.x};
        auto newY{m_position.y - 1};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::North;
        }
    }

    auto Player::moveEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveEast, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::East;
        }
    }

    auto Player::moveSouth() -> void
    {
        auto newX{m_position.x};
        auto newY{m_position.y + 1};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveSouth, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::South;
        }
    }

    auto Player::moveWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveWest, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::West;
        }
    }

    auto Player::moveNorthEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y - 1};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorthEast, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::NorthEast;
        }
    }

    auto Player::moveSouthEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y + 1};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveSouthEast, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::SouthEast;
        }
    }

    auto Player::moveSouthWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y + 1};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveSouthWest, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::SouthWest;
        }
    }

    auto Player::moveNorthWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y - 1};

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (worldArea->getTile(newX, newY)->getGround() != hash("GroundWater"))
        {
            auto objectsStack{worldArea->getTile(newX, newY)->getObjectsStack()};
            for (auto object : objectsStack->getObjects())
            {
                if (ObjectIndex::instance().getBlocksMovement(object->getType()))
                {
                    return;
                }
            }

            m_position = {newX, newY};
            m_playerActions.push_back({PlayerActionTypes::MoveNorthWest, "", m_position});
            m_playerMoveDirection = PlayerMoveDirections::NorthWest;
        }
    }

    auto Player::addExperience(int experience) -> void
    {
        m_experience += experience;
    }

    auto Player::addPlayerAction(PlayerActionTypes playerAction,
                                 std::string_view actionFirstArgument, Point actionSecondArgument)
        -> void
    {
        m_playerActions.push_back(std::tuple<PlayerActionTypes, std::string, Point>{
            playerAction, actionFirstArgument, actionSecondArgument});
    }

    PointF Player::getSmoothPosition() const
    {
        auto dx{0.0F};
        auto dy{0.0F};

        auto now{getTicks()};

        auto elapsedTime{now - m_ticksLastMovement};
        auto timeForOneStep{static_cast<int>(invertSpeed(m_movementSpeed))};

        auto moveProgress{static_cast<float>(elapsedTime) / timeForOneStep};

        if (moveProgress > 1.0F)
        {
            moveProgress = 0.0F;
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
