/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Geometry.hpp"
// clang-format on

namespace ForradiaEngine
{
    /* Point types */ // clang-format off
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

        auto Point::operator=(const Point &other) -> Point &
        {
            this->x = other.x;
            this->y = other.y;

            return *this;
        }

        auto PointF::operator+(const PointF &other) const -> PointF
        {
            return {this->x + other.x, this->y + other.y};
        }

        auto PointF::operator-(const PointF &other) const -> PointF
        {
            return {this->x - other.x, this->y - other.y};
        }
    // clang-format on

    /* Rectangle types */ // clang-format off
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
    // clang-format on
}