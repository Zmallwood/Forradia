/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Model.hpp"

namespace Forradia {
  auto Model::GetIndices(aiMesh *mesh) const -> Vector<unsigned int> {
    Vector<unsigned int> indices;

    // Iterate over all faces.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      // Access the face.
      auto face{mesh->mFaces[i]};

      // Iterate over all indices in the face.
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }
    return indices;
  }
}
