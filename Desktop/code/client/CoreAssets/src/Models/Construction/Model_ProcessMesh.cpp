/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Model.hpp"

namespace Forradia {
  auto Model::ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
      -> GLMMesh {
    auto vertices{Model::GetVertices(mesh, transformation)};
    auto indices{Model::GetIndices(mesh)};
    auto textures{Model::GetTextures(mesh, scene)};
    return {vertices, indices, textures};
  }
}
