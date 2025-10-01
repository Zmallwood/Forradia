/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "rect_f.hpp"

namespace forr {
  bool RectF::Contains(PointF point) {
    // Create condition by checking against the boundaries of this rectangle.
    return point.x >= x && point.y >= y && point.x < x + width &&
           point.y < y + height;
  }

  PointF RectF::GetPosition() const {
    // Return only the coordinates.
    return {x, y};
  }

  void RectF::Offset(PointF offset) {
    // Add the offset to the dimensions separately.
    x += offset.x;
    y += offset.y;
  }
}