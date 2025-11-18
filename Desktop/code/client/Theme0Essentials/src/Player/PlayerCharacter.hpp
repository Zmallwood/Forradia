//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "PlayerBody.hpp"

namespace Forradia::Theme0::GameplayCore
{
    class PlayerObjectsInventory;

    class PlayerCharacter
    {
      public:
        PlayerCharacter()
        {
            Initialize();
        }

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

        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        void SetTicksLastMovement(int value)
        {
            m_ticksLastMovement = value;
        }

        auto GetDestination() const
        {
            return m_destination;
        }

        void SetDestination(Point value)
        {
            m_destination = value;
        }

        auto &GetBodyRef()
        {
            return m_body;
        }

        auto GetMoney() const
        {
            return m_money;
        }

        auto &GetObjectsInventoryRef() const
        {
            return *m_playerObjectsInventory;
        }

      private:
        void Initialize();

        void MoveToSuitablePosition();

        String m_name{"Unnamed Player"};

        Point m_position{60, 50};

        float m_movementSpeed{5.0f};

        int m_ticksLastMovement{0};

        Point m_destination{-1, -1};

        PlayerBody m_body;

        int m_money{0};

        SharedPtr<PlayerObjectsInventory> m_playerObjectsInventory;
    };
}