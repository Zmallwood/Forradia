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

    private:
        Point m_position{60, 50};
        float m_movementSpeed{5.0f};
        int m_ticksLastMove{0};
    };
}