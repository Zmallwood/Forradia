/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "RectF.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto RectF::contains(PointF point) const -> bool
    {
        return point.x >= this->x && point.y >= this->y && point.x < this->x + this->width &&
               point.y < this->y + this->height;
    }

    auto RectF::getPosition() const -> PointF
    {
        return {this->x, this->y};
    }

    auto RectF::offset(PointF offset) -> void
    {
        this->x += offset.x;
        this->y += offset.y;
    }
}
