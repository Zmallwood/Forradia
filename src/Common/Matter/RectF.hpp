/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Point.hpp"

namespace Forradia
{
    class RectF
    {
    public:
        bool Contains(PointF point);

        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};
    };
}