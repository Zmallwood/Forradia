#pragma once

namespace Forradia
{
    class WorldArea;

    class World
    {
    public:
        World();

        auto GetCurrentWorldArea() const
        {
            return m_currentWorldArea;
        }

    private:
        std::shared_ptr<WorldArea> m_currentWorldArea;
    };
}