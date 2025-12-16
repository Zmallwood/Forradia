//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Model.hpp"

namespace Forradia {
GLMMesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation) const {
  auto vertices{this->GetVertices(mesh, transformation)};
  auto indices{this->GetIndices(mesh)};
  auto textures{this->GetTextures(mesh, scene)};
  return GLMMesh(vertices, indices, textures);
}
}