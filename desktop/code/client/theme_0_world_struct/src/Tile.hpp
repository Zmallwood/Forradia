//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Directions.hpp"

namespace Forradia::Theme0
{
    class ObjectsStack;

    class Creature;

    class Robot;

    class Tile
    {
      public:
        Tile()
        {
            this->Initialize();
        }

        auto GetGround() const
        {
            return m_ground;
        }

        void SetGround(StringView ground_name);

        auto GetObjectsStack() const
        {
            return m_objectsStack;
        }

        auto GetCreature() const
        {
            return m_creature;
        }

        void SetCreature(
            SharedPtr<Forradia::Theme0::Creature> val)
        {
            m_creature = val;
        }

        auto GetRobot() const
        {
            return m_robot;
        }

        void
        SetRobot(SharedPtr<Forradia::Theme0::Robot> val)
        {
            m_robot = val;
        }

        auto GetElevation() const
        {
            return m_elevation;
        }

        void SetElevation(int value)
        {
            m_elevation = value;
        }

        auto GetWaterDepth() const
        {
            return m_waterDepth;
        }

        void SetWaterDepth(int value)
        {
            m_waterDepth = value;
        }

        auto GetRiverDirection1() const
        {
            return m_riverDirection1;
        }

        void SetRiverDirection1(Directions value)
        {
            m_riverDirection1 = value;
        }

        auto GetRiverDirection2() const
        {
            return m_riverDirection2;
        }

        void SetRiverDirection2(Directions value)
        {
            m_riverDirection2 = value;
        }

      private:
        void Initialize();

        int m_ground{0};

        SharedPtr<Forradia::Theme0::ObjectsStack>
            m_objectsStack;

        SharedPtr<Forradia::Theme0::Creature> m_creature;

        SharedPtr<Forradia::Theme0::Robot> m_robot;

        int m_elevation{0};

        int m_waterDepth{0};

        Directions m_riverDirection1{Directions::None};

        Directions m_riverDirection2{Directions::None};
    };
}