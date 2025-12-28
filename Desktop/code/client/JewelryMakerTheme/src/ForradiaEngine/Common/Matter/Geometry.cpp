/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Geometry.hpp"

namespace ForradiaEngine
{
    auto Point::operator==(const Point &other) const -> bool
    {
        return other.x == this->x && other.y == this->y;
    }

    auto Point::operator<(const Point &other) const -> bool
    {
        if (this->x != other.x)
        {
            return this->x < other.x;
        }

        return this->y < other.y;
    }

    auto PointF::operator+(const PointF &other) const -> PointF
    {
        return {this->x + other.x, this->y + other.y};
    }

    auto PointF::operator-(const PointF &other) const -> PointF
    {
        return {this->x - other.x, this->y - other.y};
    }

    auto Point3::offset(Point3 offset) -> Point3
    {
        return {this->x + offset.x, this->y + offset.y, this->z + offset.z};
    }

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