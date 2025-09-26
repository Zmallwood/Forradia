#pragma once

namespace Forradia
{
    class Engine
    {
    public:
        void Run();

        void Stop();

        void PollEvents();

    private:
        bool m_running{true};
    };
}
