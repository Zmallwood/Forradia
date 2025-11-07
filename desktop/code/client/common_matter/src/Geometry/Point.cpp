//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Point.hpp"

namespace Forradia
{
    bool Point::operator==(const Point &other) const
    {
        // Compare x and y dimensions.

        return other.x == this->x && other.y == this->y;
    }
}