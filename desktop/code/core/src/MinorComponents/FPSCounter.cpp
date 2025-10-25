//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "FPSCounter.hpp"

namespace Forradia
{

    void FPSCounter::Update()
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