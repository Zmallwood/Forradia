/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "PointF.hpp"

namespace Forradia {
  PointF PointF::operator+(const PointF &other) const {
    // Sum the dimensions of the two points.
    return {x + other.x, y + other.y};
  }

  PointF PointF::operator-(const PointF &other) const {
    // Subract the dimensions of the other point from this point.
    return {x - other.x, y - other.y};
  }
}