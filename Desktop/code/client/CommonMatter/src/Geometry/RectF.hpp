/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "PointF.hpp"

namespace Forradia
{
    /**
        A rectangle in 2D space using dimensions of float type.
     */
    class RectF
    {
      public:
        /**
            Check if this rectangle contains a certain point.

            @param point Point to check if it is contained in this rectangle.
            @return True if the Point is within this rectangle, otherwise false.
         */
        [[nodiscard]] auto contains(PointF point) const -> bool;

        /**
            Returns only the position of this rectangle.

            @return The position.
         */
        [[nodiscard]] auto getPosition() const -> PointF;

        /**
            Adds an offset to this rectangle, with the dimensions altered separately.

            @param offset The offset to add.
         */
        auto offset(PointF offset) -> void;

        float x{0.0F};      ///< The x coordinate.
        float y{0.0F};      ///< The y coordinate.
        float width{0.0F};  ///< The width in the x dimension.
        float height{0.0F}; ///< The height in the y dimension.
    };
}
