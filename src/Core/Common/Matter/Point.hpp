/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class Point
    {
    public:
        bool operator==(const Point& other) const;

        int x{0};
        int y{0};
    };
}
