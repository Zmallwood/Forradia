#include "FPSCounter.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"

namespace Forradia
{
    void FPSCounter::Update()
    {
        auto now{GetTicks()};

        if (now > m_ticksLastUpdate + k_oneSecondMillis)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }

        ++m_framesCount;
    }

    void FPSCounter::Render() const
    {
        auto fpsText{"FPS: " + std::to_string(m_fps)};

        _<TextRenderer>().DrawString(
            fpsText,
            0.93f,
            0.02f);
    }
}
