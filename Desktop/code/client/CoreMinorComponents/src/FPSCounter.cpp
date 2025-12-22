/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "FPSCounter.hpp"
#include "Constants.hpp"
#include "TimeUtilities.hpp"

namespace Forradia
{
    auto FPSCounter::Update() -> void
    {
        auto now{GetTicks()};

        if (now > m_ticksLastUpdate + k_oneSecMillis)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }
        ++m_framesCount;
    }
}
