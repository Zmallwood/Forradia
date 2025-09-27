/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

 #include "Point.hpp"

 namespace Forradia
 {
    bool Point::operator==(const Point& other) const
    {
        return other.x == x && other.y == y;
    }
 }