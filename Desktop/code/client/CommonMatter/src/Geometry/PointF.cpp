/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "PointF.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto PointF::operator+(const PointF &other) const -> PointF {
  return {this->x + other.x, this->y + other.y};
}

auto PointF::operator-(const PointF &other) const -> PointF {
  return {this->x - other.x, this->y - other.y};
}
}
