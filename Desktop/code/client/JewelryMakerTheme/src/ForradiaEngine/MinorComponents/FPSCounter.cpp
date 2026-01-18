/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "FPSCounter.hpp"
#include "ForradiaEngine/Common/General.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"

namespace ForradiaEngine
{
    auto FPSCounter::update() -> void
    {
        auto now{getTicks()};

        If(now > m_ticksLastUpdate + k_oneSecMillis)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }

        ++m_framesCount;
    }
}
