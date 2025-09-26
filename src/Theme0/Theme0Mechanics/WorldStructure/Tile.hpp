#pragma once

namespace Forradia
{
    class ObjectsStack;
    class Mob;

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

        auto GetMob() const
        {
            return m_mob;
        }

        void SetMob(std::shared_ptr<Mob> mob)
        {
            m_mob = mob;
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
        std::shared_ptr<Mob> m_mob;
        int m_elevation{0};
    };
}