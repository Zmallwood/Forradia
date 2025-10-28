//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Model.hpp"

namespace Forradia
{
    void Model::Initialize(StringView filePath)
    {
        // Create an Assimp importer.

        Assimp::Importer importer;

        // Set the import flags.

        unsigned int flags{aiProcess_Triangulate |
                           aiProcess_FlipUVs |
                           aiProcess_CalcTangentSpace |
                           aiProcess_GenBoundingBoxes |
                           aiProcess_FixInfacingNormals};

        // Read the model file.

        const aiScene *scene{
            importer.ReadFile(filePath.data(), flags)};

        // If the model could not be loaded.

        if (nullptr == scene || nullptr == scene->mRootNode)
        {
            // Print an error message.

            PrintLine(
                "ERROR: ASSIMP could not load model: " +
                String(importer.GetErrorString()));
        }
        else
        {
            // If the model could be loaded, process it.

            this->ProcessNode(scene->mRootNode, scene,
                              aiMatrix4x4());
        }
    }
}