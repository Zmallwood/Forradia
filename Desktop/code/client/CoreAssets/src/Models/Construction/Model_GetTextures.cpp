/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"
#include "FilePathUtilities.hpp"
#include "Model.hpp"

namespace Forradia {
    auto Model::GetTextures(aiMesh *mesh, const aiScene *scene) -> std::vector<Texture> {
        if (mesh == nullptr) {
            ThrowError("mesh is nullptr");
            return {};
        }

        if (scene == nullptr) {
            ThrowError("scene is nullptr");
            return {};
        }

        std::vector<Texture> textures;
        aiString textureFilePath;

        // Get the texture path.
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0,
                                                            &textureFilePath);
        // Add the texture to the results.
        textures.emplace_back(GetFileNameNoExtension(textureFilePath.C_Str()));
        return textures;
    }
}
