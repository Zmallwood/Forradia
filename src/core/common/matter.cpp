/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "matter.hpp"

namespace forr {
  bool point::operator==(const point &other) const {
    // Compare x and y dimensions.
    return other.x == x && other.y == y;
  }

  point_f point_f::operator+(const point_f &other) const {
    // Sum the dimensions of the two points.
    return {x + other.x, y + other.y};
  }

  point_f point_f::operator-(const point_f &other) const {
    // Subract the dimensions of the other point from this point.
    return {x - other.x, y - other.y};
  }

  bool rect_f::contains(point_f point) {
    // Create condition by checking against the boundaries of this rectangle.
    return point.x >= x && point.y >= y && point.x < x + width &&
           point.y < y + height;
  }

  point_f rect_f::get_position() const {
    // Return only the coordinates.
    return {x, y};
  }

  void rect_f::offset(point_f offset) {
    // Add the offset to the dimensions separately.
    x += offset.x;
    y += offset.y;
  }

  SDL_Color color::to_sdl_color() const {
    // Calculate individual color components.
    auto rInt{c_uint8(r * 255)};
    auto gInt{c_uint8(g * 255)};
    auto bInt{c_uint8(b * 255)};
    auto aInt{c_uint8(a * 255)};
    return {rInt, gInt, bInt, aInt};
  }
}