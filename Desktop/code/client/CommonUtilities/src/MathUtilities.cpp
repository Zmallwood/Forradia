/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MathUtilities.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto ComputeNormal(const glm::vec3 &vec1, const glm::vec3 &vec2, const glm::vec3 &vec3)
    -> glm::vec3 {
  // Uses vec2 as a new origin for vec1, vec3.
  auto vecA = vec3 - vec2;
  auto vecB = vec1 - vec2;
  // Compute the cross product vecA X vecB to get the face normal.
  return glm::normalize(glm::cross(vecA, vecB));
}
}
