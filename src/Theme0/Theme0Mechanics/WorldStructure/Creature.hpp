/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class Creature
    {
    public:
        Creature(std::string_view typeName);

        auto GetType() const
        {
            return m_type;
        }

        auto GetTicksLastMove() const
        {
            return m_ticksLastMove;
        }

        void SetTicksLastMove(int ticksLastMove)
        {
            m_ticksLastMove = ticksLastMove;
        }

        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
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
        int m_type{0};
        int m_ticksLastMove{0};
        float m_movementSpeed{2.0f};
        Point m_destination{-1, -1};
    };
}