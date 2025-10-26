//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GLMVertex.hpp"

#include "Aliases.hpp"

#include "Texturing/Texture.hpp"

#include <glm/glm.hpp>

#include <assimp/scene.h>

namespace Forradia
{
    ///
    /// A mesh used primarily for models, using GLM
    /// types.
    ///
    class GLMMesh
    {
      public:
        Vector<GLMVertex> vertices; ///< The vertices.

        Vector<unsigned int> indices; ///< The indices.

        Vector<Texture> textures; ///< The textures.
    };
}