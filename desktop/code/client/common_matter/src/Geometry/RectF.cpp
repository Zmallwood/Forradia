//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "RectF.hpp"

namespace Forradia
{
    bool RectF::Contains(PointF point)
    {
        // Create condition by checking against the boundaries of this rectangle.

        return point.x >= this->x && point.y >= this->y && point.x < this->x + this->width &&
               point.y < this->y + this->height;
    }

    PointF RectF::GetPosition() const
    {
        // Return only the coordinates.

        return {this->x, this->y};
    }

    void RectF::Offset(PointF offset)
    {
        // Add the offset to the dimensions separately.

        this->x += offset.x;

        this->y += offset.y;
    }
}