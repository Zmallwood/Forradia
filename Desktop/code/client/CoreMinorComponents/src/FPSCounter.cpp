//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "FPSCounter.hpp"

namespace Forradia
{
    void FPSCounter::Update()
    {
        // Get the current time in milliseconds.

        auto now{GetTicks()};

        // If it has been more than one second since the last update:

        if (now > m_ticksLastUpdate + k_oneSecMillis)
        {
            // Update the FPS value.

            m_fps = m_framesCount;

            // Reset the frame count.

            m_framesCount = 0;

            // Update the last update time.

            m_ticksLastUpdate = now;
        }

        // Increment the frame count.

        ++m_framesCount;
    }
}