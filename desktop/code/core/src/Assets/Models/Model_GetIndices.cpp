//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Model.hpp"

namespace Forradia
{
    Vector<unsigned int> Model::GetIndices(aiMesh *mesh)
    {
        Vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face{mesh->mFaces[i]};

            for (unsigned int j = 0; j < face.mNumIndices;
                 j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        return indices;
    }
}