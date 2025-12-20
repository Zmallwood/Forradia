/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include <glm/glm.hpp>

namespace Forradia {
    /**
     * A vertex used for models using GLM types.
     */
    class GLMVertex {
      public:
        /**
         * The position.
         */
        glm::vec3 position;

        /**
         * The normal.
         */
        glm::vec3 normal;

        /**
         * The texture coordinates.
         */
        glm::vec2 uv;
    };
}
