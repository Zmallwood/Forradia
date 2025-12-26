/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine
{
    /* Point types */ // clang-format off
        /**
        *  Point in 2D space, using dimensions of int type.
        */
        class Point
        {
          public:
            /**
            *  Equality operator between two Points.
            *
            *  @param other Other Point to check equality against.
            *  @return True if the two points are equal, otherwise false.
            */
            auto operator==(const Point &other) const -> bool;

            /**
            *  Less than operator between two Points.
            *
            *  @param other Other Point to check less than against.
            *  @return True if the current point is less than the other point, otherwise false.
            */
            auto operator<(const Point &other) const -> bool;

            auto operator=(const Point &other) -> Point &;

            /**
            *  The x dimension.
            */
            int x{0};
            /**
            *  The y dimension.
            */
            int y{0};
        };

        /**
        *  Point in 2D space using dimensions of float type.
        */
        class PointF
        {
          public:
            /**
            *   Summing operator for the two points.
            *
            *  @param other The other PointF to add to this point.
            *  @return The resulting PointF with the dimensions added separately.
            */
            auto operator+(const PointF &other) const -> PointF;

            /**
            *  Subtraction operator for the two points.
            *
            *  @param other The other PointF to subtract from this point.
            *  @return The resulting PointF with the dimensions subtracted separately.
            */
            auto operator-(const PointF &other) const -> PointF;

            /**
            *  The x dimension.
            */
            float x{0.0F};
            /**
            *  The y dimension.
            */
            float y{0.0F};
        };

        /**
        *  Point in 3D space using dimensions of integer type.
        */
        class Point3
        {
          public:
            /**
            *  The x dimension.
            */
            int x{0};
            /**
            *  The y dimension.
            */
            int y{0};
            /**
            *  The z dimension.
            */
            int z{0};
        };

        /**
        *  Point in 3D space using dimensions of float type.
        */
        class Point3F
        {
          public:
            /**
            *  The x dimension.
            */
            float x{0.0F};
            /**
            *  The y dimension.
            */
            float y{0.0F};
            /**
            *  The z dimension.
            */
            float z{0.0F};
        };
    // clang-format on

    /* Size types */ // clang-format off
        /**
        *  Size in 2D space, with the dimensions as int values.
        */
        class Size
        {
          public:
            int width{0};  ///< The width.
            int height{0}; ///< The height.
        };

        /**
        *  Size in 2D space with dimensions of float values.
        */
        class SizeF
        {
          public:
            float width{0.0F};  ///< The width.
            float height{0.0F}; ///< The height.
        };
    // clang-format on

    /* Rectangle types */ // clang-format off
        /**
        *   A rectangle in 2D space using dimensions of float type.
        */
        class RectF
        {
          public:
            /**
            *  Check if this rectangle contains a certain point.
            *
            *  @param point Point to check if it is contained in this rectangle.
            *  @return True if the Point is within this rectangle, otherwise false.
            */
            [[nodiscard]] auto contains(PointF point) const -> bool;

            /**
            *  Returns only the position of this rectangle.
            *
            *  @return The position.
            */
            [[nodiscard]] auto getPosition() const -> PointF;

            /**
            *  Adds an offset to this rectangle, with the dimensions altered separately.
            *
            *  @param offset The offset to add.
            */
            auto offset(PointF offset) -> void;

            /**
            *  The x coordinate.
            */
            float x{0.0F};
            /**
            *  The y coordinate.
            */
            float y{0.0F};
            /**
            *  The width in the x dimension.
            */
            float width{0.0F};
            /**
            *  The height in the y dimension.
            */
            float height{0.0F};
        };
    // clang-format on
}