#pragma once

namespace Forradia
{
    class Mob
    {
    public:
        Mob(std::string_view typeName);

        auto GetType() const
        {
            return m_type;
        }

        auto GetLeader() const
        {
            return m_leader;
        }

        void SetLeader(std::shared_ptr<Mob> leader)
        {
            m_leader = leader;
        }

        auto GetIsLeader() const
        {
            return m_isLeader;
        }

        void SetIsLeader(bool isLeader)
        {
            m_isLeader = isLeader;
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

        auto GetOffsetLeader() const
        {
            return m_offsetLeader;
        }

        void SetOffsetLeader(Point offsetLeader)
        {
            m_offsetLeader = offsetLeader;
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
        std::shared_ptr<Mob> m_leader;
        bool m_isLeader{false};
        int m_ticksLastMove{0};
        float m_movementSpeed{2.0f};
        Point m_offsetLeader{0, 0};
        Point m_destination{-1, -1};
    };
}