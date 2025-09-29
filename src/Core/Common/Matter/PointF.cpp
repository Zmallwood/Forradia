/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "PointF.hpp"

namespace Forradia
{
    PointF PointF::operator+(const PointF &other) const
    {
        return {x + other.x, y + other.y};
    }

    PointF PointF::operator-(const PointF &other) const
    {
        return {x - other.x, y - other.y};
    }
}