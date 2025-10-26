//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    namespace Theme0
    {
        class Creature
        {
          public:
            Creature(StringView type_name)
                : m_type{Hash(type_name)}
            {
                Initialize();
            }

            auto GetType() const
            {
                return m_type;
            }

            auto GetTicksLastMovement() const
            {
                return m_ticksLastMovement;
            }

            void SetTicksLastMovement(int value)
            {
                m_ticksLastMovement = value;
            }

            auto GetMovementSpeed() const
            {
                return m_movementSpeed;
            }

            auto GetDestination() const
            {
                return m_destination;
            }

            void SetDestination(Point value)
            {
                m_destination = value;
            }

          private:
            void Initialize();

            int m_type{0};

            int m_ticksLastMovement{0};

            float m_movementSpeed{2.0f};

            Point m_destination{-1, -1};
        };
    }
}