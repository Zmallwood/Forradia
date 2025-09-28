/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class ObjectsStack;
    class Creature;

    class Tile
    {
    public:
        Tile();

        void SetGround(StringView groundName);

        auto GetGround() const
        {
            return m_ground;
        }

        auto GetObjectsStack() const
        {
            return m_objectsStack;
        }

        auto GetCreature() const
        {
            return m_creature;
        }

        void SetCreature(SharedPtr<Creature> creature)
        {
            m_creature = creature;
        }

        auto GetElevation() const
        {
            return m_elevation;
        }

        void SetElevation(int elevation)
        {
            m_elevation = elevation;
        }

        auto GetWaterDepth() const
        {
            return m_waterDepth;
        }

        void SetWaterDepth(int value)
        {
            m_waterDepth = value;
        }

    private:
        int m_ground{0};
        SharedPtr<ObjectsStack> m_objectsStack;
        SharedPtr<Creature> m_creature;
        int m_elevation{0};
        int m_waterDepth {0};
    };
}