/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Model.hpp"

namespace Forradia {
auto Model::ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation) const
    -> GLMMesh {
  auto vertices{this->GetVertices(mesh, transformation)};
  auto indices{this->GetIndices(mesh)};
  auto textures{this->GetTextures(mesh, scene)};
  return GLMMesh(vertices, indices, textures);
}
}