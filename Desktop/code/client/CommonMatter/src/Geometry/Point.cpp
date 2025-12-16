/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Point.hpp"

namespace Forradia {
bool Point::operator==(const Point &other) const {
  return other.x == this->x && other.y == this->y;
}

bool Point::operator<(const Point &other) const {
  if (this->x != other.x) {
    return this->x < other.x;
  }
  return this->y < other.y;
}
}