/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Model.hpp"

namespace Forradia {
auto Model::GetTextures(aiMesh *mesh, const aiScene *scene) const -> Vector<Texture> {
  Vector<Texture> textures;
  aiString textureFilePath;

  // Get the texture path.
  scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
  // Add the texture to the results.
  textures.push_back(Texture(GetFileNameNoExtension(textureFilePath.C_Str())));
  return textures;
}
}