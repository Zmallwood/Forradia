/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "Model.hpp"
// clang-format on

namespace ForradiaEngine
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
