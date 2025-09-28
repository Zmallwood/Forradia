/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

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
        const PointF k_position{0.93f, 0.02f};
    };
}