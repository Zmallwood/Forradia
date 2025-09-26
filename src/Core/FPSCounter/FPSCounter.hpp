#pragma once

namespace Forradia
{
    class FPSCounter
    {
    public:
        void Update();

        void Render() const;

    private:
        int m_fps{0};
        int m_framesCount{0};
        int m_ticksLastUpdate{0};
    };
}