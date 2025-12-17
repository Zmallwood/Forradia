/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Point.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto Point::operator==(const Point &other) const -> bool {
  return other.x == this->x && other.y == this->y;
}

auto Point::operator<(const Point &other) const -> bool {
  if (this->x != other.x)
    return this->x < other.x;
  return this->y < other.y;
}
}
