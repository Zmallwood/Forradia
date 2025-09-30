/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  /**
   * \brief Point in 2D space using dimensions of float type.
   */
  class PointF {
  public:
    /**
     * \brief Summing operator for the two points.
     *
     * \param other The other PointF to add to this point.
     * \return The resulting PointF with the dimensions added separately.
     */
    PointF operator+(const PointF &other) const;

    /**
     * \brief Subtraction operator for the two points.
     *
     * \param other The other PointF to subtract from this point.
     * \return The resulting PointF with the dimensions subtracted separetely.
     */
    PointF operator-(const PointF &other) const;

    float x{0.0f}; ///< The x dimension.
    float y{0.0f}; ///< The y dimension.
  };
}