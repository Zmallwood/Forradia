/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"
#include "FilePathUtilities.hpp"
#include "Model.hpp"

namespace Forradia
{
    auto Model::getTextures(aiMesh *mesh, const aiScene *scene) -> std::vector<Texture>
    {
        if (mesh == nullptr)
        {
            throwError("mesh is nullptr");
        }

        if (scene == nullptr)
        {
            throwError("scene is nullptr");
        }

        std::vector<Texture> textures;
        aiString textureFilePath;

        // Get the texture path.
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0,
                                                            &textureFilePath);
        // Add the texture to the results.
        textures.emplace_back(getFileNameNoExtension(textureFilePath.C_Str()));

        return textures;
    }
}
