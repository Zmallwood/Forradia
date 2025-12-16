//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once
#include <glm/glm.hpp>

namespace Forradia {
    /// A vertex used for models using GLM types.
    class GLMVertex {
      public:
        glm::vec3 position; ///< The position.
        glm::vec3 normal;   ///< The normal.
        glm::vec2 uv;       ///< The texture coordinates.
    };
}