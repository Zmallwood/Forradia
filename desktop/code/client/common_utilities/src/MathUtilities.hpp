//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Compute the normal of a triangle.
    ///
    /// @param p1 First point.
    /// @param p2 Second point.
    /// @param p3 Third point.
    /// @return Normal.
    ///
    glm::vec3 ComputeNormal(const glm::vec3 &p1,
                            const glm::vec3 &p2,
                            const glm::vec3 &p3);
}