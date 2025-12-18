/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  /**
   * Point in 2D space using dimensions of float type.
   */
  class PointF {
   public:
    /**
     * Summing operator for the two points.
     *
     * @param other The other PointF to add to this point.
     * @return The resulting PointF with the dimensions added separately.
     */
    auto operator+(const PointF &other) const -> PointF;

    /**
     * Subtraction operator for the two points.
     *
     * @param other The other PointF to subtract from this point.
     * @return The resulting PointF with the dimensions subtracted separetely.
     */
    auto operator-(const PointF &other) const -> PointF;

    /**
     * The x dimension.
     */
    float x{0.0F};

    /**
     * The y dimension.
     */
    float y{0.0F};
  };
}
