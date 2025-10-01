/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "point.hpp"

namespace forr {
  /**
   * \brief A rectangle in 2D space using dimensions of float type.
   */
  class RectF {
  public:
    /**
     * \brief Check if this rectangle contains a certian point.
     *
     * \param point Point to check if it is contained in this rectangle.
     * \return True if the Point is within this rectangle, otherwise false.
     */
    bool Contains(PointF point);

    /**
     * \brief Returns only the position of this rectangle.
     *
     * \return The position.
     */
    PointF GetPosition() const;

    /**
     * \brief Adds an offset to this rectangle, with the dimensions altered
     * separately.
     *
     * \param offset The offset to add.
     */
    void Offset(PointF offset);

    float x{0.0f};      ///< The x coordinate.
    float y{0.0f};      ///< The y coordinate.
    float width{0.0f};  ///< The width, in the x dimension.
    float height{0.0f}; ///< The height, in the y dimension.
  };
}