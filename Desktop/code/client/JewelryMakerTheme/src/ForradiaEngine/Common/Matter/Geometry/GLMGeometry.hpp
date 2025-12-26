/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Texturing/Texture.hpp"
    #include <vector>
    #include <string>
    #include <glm/glm.hpp>
// clang-format on

namespace ForradiaEngine
{
    /**
        A vertex used for models using GLM types.
    */
    class GLMVertex
    {
      public:
        glm::vec3 position{}; ///< The position.
        glm::vec3 normal{};   ///< The normal.
        glm::vec2 uv{};       ///< The texture coordinates.
    };

    /**
     *  A texture, primarily used for models.
     */
    class Texture
    {
      public:
        /**
         *  Constructor for the Texture class.
         *
         *  @param path The path to the texture.
         */
        Texture(std::string_view path) : path(path)
        {
        }

        std::string path{}; ///< The path to the texture.
    };

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
