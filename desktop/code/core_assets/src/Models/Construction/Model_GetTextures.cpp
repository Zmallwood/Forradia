//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Model.hpp"

namespace Forradia
{
    Vector<Texture> Model::GetTextures(aiMesh *mesh,
                                       const aiScene *scene)
    {
        Vector<Texture> textures;

        aiString s;

        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(
            aiTextureType_DIFFUSE, 0, &s);

        textures.push_back(
            Texture(GetFileNameNoExtension(s.C_Str())));

        return textures;
    }
}