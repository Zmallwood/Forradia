/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GLMVertex.hpp"
#include "ForradiaEngine/Common/Matter/Texturing/Texture.hpp"
#include <vector>

namespace Forradia
{
    /**
        A mesh used primarily for models, using GLM types.
     */
    class GLMMesh
    {
      public:
        /**
             Constructor for the GLMMesh class.

            @param vertices The vertices of the mesh.
            @param indices The indices of the mesh.
            @param textures The textures of the mesh.
         */
        GLMMesh(std::vector<GLMVertex> vertices, std::vector<unsigned int> indices,
                std::vector<Texture> textures)
            : vertices(std::move(vertices)), indices(std::move(indices)),
              textures(std::move(textures))
        {
        }

        std::vector<GLMVertex> vertices{};   ///< The vertices.
        std::vector<unsigned int> indices{}; ///< The indices.
        std::vector<Texture> textures{};     ///< The textures.
    };
}
