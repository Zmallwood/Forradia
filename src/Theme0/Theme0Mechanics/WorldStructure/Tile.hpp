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

        void SetGround(std::string_view groundName);

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

        void SetCreature(std::shared_ptr<Creature> creature)
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

    private:
        int m_ground{0};
        std::shared_ptr<ObjectsStack> m_objectsStack;
        std::shared_ptr<Creature> m_creature;
        int m_elevation{0};
    };
}