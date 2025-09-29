/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "RectF.hpp"

namespace Forradia
{
    bool RectF::Contains(PointF point)
    {
        return point.x >= x &&
               point.y >= y &&
               point.x < x + width &&
               point.y < y + height;
    }

    PointF RectF::GetPosition() const
    {
        return {x, y};
    }

    void RectF::Offset(PointF offset)
    {
        x += offset.x;
        y += offset.y;
    }
}