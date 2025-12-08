//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Point.hpp"

namespace Forradia
{
    bool Point::operator==(const Point &other) const
    {
        // Compare x and y dimensions for this point and the other point.
        return other.x == this->x && other.y == this->y;
    }

    bool Point::operator<(const Point &other) const
    {
        // Compare x and y dimensions using lexicographic ordering.
        // First compare x, then y if x values are equal.

        if (this->x != other.x)
        {
            return this->x < other.x;
        }

        return this->y < other.y;
    }
}