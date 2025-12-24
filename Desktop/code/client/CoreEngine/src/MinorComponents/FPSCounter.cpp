/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "FPSCounter.hpp"
#include "Common/General/Constants.hpp"
#include "Common/Utilities/TimeUtilities.hpp"

namespace Forradia
{
    auto FPSCounter::update() -> void
    {
        auto now{getTicks()};

        if (now > m_ticksLastUpdate + k_oneSecMillis)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }

        ++m_framesCount;
    }
}
