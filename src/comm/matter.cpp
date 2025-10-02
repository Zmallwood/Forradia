/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "matter.hpp"

namespace forr {
  bool point::operator==(const point &p) const {
    // Compare x and y dimensions.
    return p.x == x && p.y == y;
  }

  point_f point_f::operator+(const point_f &p) const {
    // Sum the dimensions of the two points.
    return {x + p.x, y + p.y};
  }

  point_f point_f::operator-(const point_f &p) const {
    // Subract the dimensions of the other point from this point.
    return {x - p.x, y - p.y};
  }

  bool rect_f::contains(point_f p) {
    // Create condition by checking against the boundaries of this rectangle.
    return p.x >= x && p.y >= y && p.x < x + w && p.y < y + h;
  }

  point_f rect_f::get_position() const {
    // Return only the coordinates.
    return {x, y};
  }

  void rect_f::offset(point_f offs) {
    // Add the offset to the dimensions separately.
    x += offs.x;
    y += offs.y;
  }

  SDL_Color color::to_sdl_color() const {
    // Calculate individual color components.
    auto r_int{c_uint8(r * 255)};
    auto g_int{c_uint8(g * 255)};
    auto b_int{c_uint8(b * 255)};
    auto a_int{c_uint8(a * 255)};
    return {r_int, g_int, b_int, a_int};
  }
}