/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MathUtilities.hpp"

namespace Forradia {
glm::vec3 ComputeNormal(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
  // Uses p2 as a new origin for p1, p3.
  auto a = p3 - p2;
  auto b = p1 - p2;
  // Compute the cross product a X b to get the face normal.
  return glm::normalize(glm::cross(a, b));
}
}