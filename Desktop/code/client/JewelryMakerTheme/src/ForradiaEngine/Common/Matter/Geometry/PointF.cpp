/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "PointF.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto PointF::operator+(const PointF &other) const -> PointF
    {
        return {this->x + other.x, this->y + other.y};
    }

    auto PointF::operator-(const PointF &other) const -> PointF
    {
        return {this->x - other.x, this->y - other.y};
    }
}
