/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
    #include "Model.hpp"
    #include "assimp/scene.h"
// clang-format on

namespace ForradiaEngine
{
    auto Model::getIndices(aiMesh *mesh) -> std::vector<unsigned int>
    {
        if (mesh == nullptr)
        {
            throwError("mesh is null");
        }

        std::vector<unsigned int> indices;

        // Iterate over all faces.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            // Access the face.
            auto face{mesh->mFaces[i]};

            // Iterate over all indices in the face.
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }
        return indices;
    }
}
