/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class Player
    {
    public:
        void MoveNorth();

        void MoveEast();

        void MoveSouth();

        void MoveWest();

        auto GetName() const
        {
            return m_name;
        }

        auto GetPosition() const
        {
            return m_position;
        }

        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        auto GetTicksLastMove() const
        {
            return m_ticksLastMove;
        }

        void SetTicksLastMove(int ticks)
        {
            m_ticksLastMove = ticks;
        }

        auto GetDestination() const
        {
            return m_destination;
        }

        void SetDestination(Point destination)
        {
            m_destination = destination;
        }

    private:
        std::string m_name{"Unnamed Player"};
        Point m_position{60, 50};
        float m_movementSpeed{5.0f};
        int m_ticksLastMove{0};
        Point m_destination{-1, -1};
    };
}