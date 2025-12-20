/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <glm/glm.hpp>

namespace Forradia {
    /**
     * Compute the normal of a triangle.
     *
     * @param p1 First point.
     * @param p2 Second point.
     * @param p3 Third point.
     * @return Normal.
     */
    auto ComputeNormal(const glm::vec3 &vec1, const glm::vec3 &vec2, const glm::vec3 &vec3)
        -> glm::vec3;
}
