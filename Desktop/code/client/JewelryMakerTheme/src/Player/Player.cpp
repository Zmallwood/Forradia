/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Player.hpp"
#include <algorithm>
#include "Properties/ObjectIndex.hpp"
#include "WorldStructure/Object.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Common/General.hpp"
#include "PlayerObjectsInventory.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto Player::initialize() -> void
    {
        m_playerObjectsInventory = std::make_shared<PlayerObjectsInventory>();

        this->moveToSuitablePosition();
    }

    auto Player::moveToSuitablePosition() -> void
    {
        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};
        auto size{worldArea->getSize()};

        m_position = {size.width / 2, size.height / 2};

        while (worldArea->getTile(m_position)->getGround() == hash("GroundWater"))
        {
            m_position = {getRandomInt(size.width), getRandomInt(size.height)};
        }
    }

    // NOLINTNEXTLINE(readability-make-member-function-const)
    auto Player::moveToPositionPossible(Point position) -> bool
    {
        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};
        auto tile{worldArea->getTile(position)};

        if (tile->getGround() == hash("GroundWater"))
        {
            return false;
        }

        auto objectsStack{tile->getObjectsStack()};

        if (std::ranges::any_of(
                objectsStack->getObjects(), [](const auto &object)
                { return ObjectIndex::instance().getBlocksMovement(object->getType()); }))
        {
            return false;
        }

        return true;
    }

    auto Player::updateRotationDegrees() -> void
    {
        switch (m_playerMoveDirection)
        {
        case PlayerMoveDirections::North:
            m_rotationDegrees = 360.0F;
            break;

        case PlayerMoveDirections::East:
            m_rotationDegrees = 90.0F;
            break;

        case PlayerMoveDirections::South:
            m_rotationDegrees = 180.0F;
            break;

        case PlayerMoveDirections::West:
            m_rotationDegrees = 270.0F;
            break;

        case PlayerMoveDirections::NorthEast:
            m_rotationDegrees = 45.0F;
            break;

        case PlayerMoveDirections::SouthEast:
            m_rotationDegrees = 135.0F;
            break;

        case PlayerMoveDirections::SouthWest:
            m_rotationDegrees = 225.0F;
            break;

        case PlayerMoveDirections::NorthWest:
            m_rotationDegrees = 315.0F;
            break;

        case PlayerMoveDirections::None:
            break;
        }
    }

    auto Player::update() -> void
    {
        auto now{getTicks()};

        this->updateRotationDegrees();

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
                this->moveNorthEast();
                break;

            case PlayerMoveDirections::SouthEast:
                this->moveSouthEast();
                break;

            case PlayerMoveDirections::SouthWest:
                this->moveSouthWest();
                break;

            case PlayerMoveDirections::NorthWest:
                this->moveNorthWest();
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
        if (this->moveToPositionPossible({m_position.x, m_position.y - 1}))
        {
            m_playerMoveDirection = PlayerMoveDirections::North;
        }
    }

    auto Player::startMovingEast() -> void
    {
        if (this->moveToPositionPossible({m_position.x + 1, m_position.y}))
        {
            m_playerMoveDirection = PlayerMoveDirections::East;
        }
    }

    auto Player::startMovingSouth() -> void
    {
        if (this->moveToPositionPossible({m_position.x, m_position.y + 1}))
        {
            m_playerMoveDirection = PlayerMoveDirections::South;
        }
    }

    auto Player::startMovingWest() -> void
    {
        if (this->moveToPositionPossible({m_position.x - 1, m_position.y}))
        {
            m_playerMoveDirection = PlayerMoveDirections::West;
        }
    }

    auto Player::startMovingNorthWest() -> void
    {
        if (this->moveToPositionPossible({m_position.x - 1, m_position.y - 1}))
        {
            m_playerMoveDirection = PlayerMoveDirections::NorthWest;
        }
    }

    auto Player::startMovingNorthEast() -> void
    {
        if (this->moveToPositionPossible({m_position.x + 1, m_position.y - 1}))
        {
            m_playerMoveDirection = PlayerMoveDirections::NorthEast;
        }
    }

    auto Player::startMovingSouthWest() -> void
    {
        if (this->moveToPositionPossible({m_position.x - 1, m_position.y + 1}))
        {
            m_playerMoveDirection = PlayerMoveDirections::SouthWest;
        }
    }

    auto Player::startMovingSouthEast() -> void
    {
        if (this->moveToPositionPossible({m_position.x + 1, m_position.y + 1}))
        {
            m_playerMoveDirection = PlayerMoveDirections::SouthEast;
        }
    }

    auto Player::stopMoving() -> void
    {
        m_playerMoveDirection = PlayerMoveDirections::None;
    }

    auto Player::moveNorth() -> void
    {
        auto newX{m_position.x};
        auto newY{m_position.y - 1};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveNorth, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::North;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveEast, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::East;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveSouth() -> void
    {
        auto newX{m_position.x};
        auto newY{m_position.y + 1};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveSouth, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::South;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveWest, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::West;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveNorthEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y - 1};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveNorthEast, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::NorthEast;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveSouthEast() -> void
    {
        auto newX{m_position.x + 1};
        auto newY{m_position.y + 1};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveSouthEast, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::SouthEast;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveSouthWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y + 1};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveSouthWest, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::SouthWest;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
        }
    }

    auto Player::moveNorthWest() -> void
    {
        auto newX{m_position.x - 1};
        auto newY{m_position.y - 1};

        if (this->moveToPositionPossible({newX, newY}) == false)
        {
            this->stopMoving();

            return;
        }

        auto worldArea{World::instance().getWorldArea(this->getWorldAreaCoordinate())};

        m_position = {newX, newY};
        m_playerActions.emplace_back(PlayerActionTypes::MoveNorthWest, "", m_position);
        m_playerMoveDirection = PlayerMoveDirections::NorthWest;

        if (worldArea->getTile(newX, newY)
                ->getObjectsStack()
                ->countHasObject("ObjectMineEntrance") > 0)
        {
            auto worldAreaCoordinateZ{m_worldAreaCoordinate.z};
            int newWorldAreaCoordinateZ{};

            if (worldAreaCoordinateZ == 0)
            {
                newWorldAreaCoordinateZ = -1;
            }
            else
            {
                newWorldAreaCoordinateZ = 0;
            }

            m_worldAreaCoordinate = {m_worldAreaCoordinate.x, m_worldAreaCoordinate.y,
                                     newWorldAreaCoordinateZ};
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
        m_playerActions.emplace_back(playerAction, actionFirstArgument, actionSecondArgument);
    }

    auto Player::getSmoothPosition() const -> PointF
    {
        auto deltaX{0.0F};
        auto deltaY{0.0F};

        auto now{getTicks()};

        auto elapsedTime{now - m_ticksLastMovement};
        auto timeForOneStep{static_cast<int>(invertSpeed(m_movementSpeed))};

        auto moveProgress{static_cast<float>(elapsedTime) / timeForOneStep};

        if (moveProgress >= 1.0F)
        {
            moveProgress = 0.0F;
            return {static_cast<float>(m_position.x), static_cast<float>(m_position.y)};
        }

        switch (m_playerMoveDirection)
        {
        case PlayerMoveDirections::North:
            deltaY = 1.0F - moveProgress;
            break;

        case PlayerMoveDirections::East:
            deltaX = -1.0F + moveProgress;
            break;

        case PlayerMoveDirections::South:
            deltaY = -1.0F + moveProgress;
            break;

        case PlayerMoveDirections::West:
            deltaX = 1.0F - moveProgress;
            break;

        case PlayerMoveDirections::NorthEast:
            deltaX = -1.0F + moveProgress;
            deltaY = 1.0F - moveProgress;
            break;

        case PlayerMoveDirections::SouthEast:
            deltaX = -1.0F + moveProgress;
            deltaY = -1.0F + moveProgress;
            break;

        case PlayerMoveDirections::SouthWest:
            deltaX = 1.0F - moveProgress;
            deltaY = -1.0F + moveProgress;
            break;

        case PlayerMoveDirections::NorthWest:
            deltaX = 1.0F - moveProgress;
            deltaY = 1.0F - moveProgress;
            break;

        case PlayerMoveDirections::None:
            break;
        }

        auto position{m_position};

        return {position.x + deltaX, position.y + deltaY};
    }
}
