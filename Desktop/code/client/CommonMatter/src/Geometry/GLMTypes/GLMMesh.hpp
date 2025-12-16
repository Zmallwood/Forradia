//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once
#include "GLMVertex.hpp"
#include "Texturing/Texture.hpp"

namespace Forradia {
/// A mesh used primarily for models, using GLM types.
class GLMMesh {
 public:
  GLMMesh(Vector<GLMVertex> vertices, Vector<unsigned int> indices, Vector<Texture> textures)
      : vertices(vertices), indices(indices), textures(textures) {
  }

  Vector<GLMVertex> vertices;   ///< The vertices.
  Vector<unsigned int> indices; ///< The indices.
  Vector<Texture> textures;     ///< The textures.
};
}