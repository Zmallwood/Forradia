/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Entity.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto Entity::initialize() -> void
    {
        // Multiply movement speed by a random number between 0.5 and 2.
        m_movementSpeed *= (getRandomInt(3) + 1) / 2.0F;
    }

    auto Entity::getSmoothPosition(Point position) const -> PointF
    {
        auto dx{0.0F};
        auto dy{0.0F};

        auto now{getTicks()};

        auto elapsedTime{now - m_ticksLastMovement};
        auto timeForOneStep{static_cast<int>(invertSpeed(m_movementSpeed))};

        auto moveProgress{static_cast<float>(elapsedTime) / timeForOneStep};

        If(moveProgress >= 1.0F)
        {
            moveProgress = 0.0F;
            return {static_cast<float>(position.x), static_cast<float>(position.y)};
        }

        switch (m_direction)
        {
        case Directions::North:
            dy = 1.0f - moveProgress;
            break;

        case Directions::East:
            dx = -1.0f + moveProgress;
            break;

        case Directions::South:
            dy = -1.0f + moveProgress;
            break;

        case Directions::West:
            dx = 1.0f - moveProgress;
            break;

        case Directions::NorthEast:
            dx = -1.0f + moveProgress;
            dy = 1.0f - moveProgress;
            break;

        case Directions::SouthEast:
            dx = -1.0f + moveProgress;
            dy = -1.0f + moveProgress;
            break;

        case Directions::SouthWest:
            dx = 1.0f - moveProgress;
            dy = -1.0f + moveProgress;
            break;

        case Directions::NorthWest:
            dx = 1.0f - moveProgress;
            dy = 1.0f - moveProgress;
            break;

        case Directions::None:
            break;
        }

        return {position.x + dx, position.y + dy};
    }
    auto Entity::update() -> void
    {
        this->updateRotationDegrees();
    }

    auto Entity::updateRotationDegrees() -> void
    {
        switch (m_direction)
        {
        case Directions::North:
            m_rotationDegrees = 360.0F + 90.0F;
            break;

        case Directions::East:
            m_rotationDegrees = 90.0F + 90.0F;
            break;

        case Directions::South:
            m_rotationDegrees = 180.0F + 90.0F;
            break;

        case Directions::West:
            m_rotationDegrees = 270.0F + 90.0F;
            break;

        case Directions::NorthEast:
            m_rotationDegrees = 45.0F + 90.0F;
            break;

        case Directions::SouthEast:
            m_rotationDegrees = 135.0F + 90.0F;
            break;

        case Directions::SouthWest:
            m_rotationDegrees = 225.0F + 90.0F;
            break;

        case Directions::NorthWest:
            m_rotationDegrees = 315.0F + 90.0F;
            break;

        case Directions::None:
            break;
        }
    }
}
