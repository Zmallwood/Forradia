/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class PointF
    {
    public:
        PointF operator+(const PointF &other) const;

        PointF operator-(const PointF &other) const;

        float x{0.0f};
        float y{0.0f};
    };
}