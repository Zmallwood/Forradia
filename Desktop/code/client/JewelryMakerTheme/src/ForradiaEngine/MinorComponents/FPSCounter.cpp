/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "FPSCounter.hpp"
    #include "ForradiaEngine/Common/General/Constants.hpp"
    #include "ForradiaEngine/Common/Utilities/TimeUtilities.hpp"
// clang-format on

namespace ForradiaEngine
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
