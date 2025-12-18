/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GLMVertex.hpp"
#include "Texturing/Texture.hpp"

namespace Forradia {
  /**
   * A mesh used primarily for models, using GLM types.
   */
  class GLMMesh {
   public:
    /**
     * Constructor for the GLMMesh class.
     *
     * @param vertices The vertices of the mesh.
     * @param indices The indices of the mesh.
     * @param textures The textures of the mesh.
     */
    GLMMesh(Vector<GLMVertex> vertices, Vector<unsigned int> indices, Vector<Texture> textures)
        : vertices(std::move(vertices)), indices(std::move(indices)),
          textures(std::move(textures)) {
    }

    /**
     * The vertices.
     */
    Vector<GLMVertex> vertices;

    /**
     * The indices.
     */
    Vector<unsigned int> indices;

    /**
     * The textures.
     */
    Vector<Texture> textures;
  };
}
