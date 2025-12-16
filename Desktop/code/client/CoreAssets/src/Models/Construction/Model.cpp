//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Model.hpp"

namespace Forradia {
    void Model::Initialize(StringView filePath) {
        Assimp::Importer importer;
        unsigned int flags{aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
                           aiProcess_GenBoundingBoxes | aiProcess_FixInfacingNormals};

        // Read the model file.
        const aiScene *scene{importer.ReadFile(filePath.data(), flags)};

        if (nullptr == scene || nullptr == scene->mRootNode) {
            PrintLine("ERROR: ASSIMP could not load model: " + String(importer.GetErrorString()));
        } else {
            this->ProcessNode(scene->mRootNode, scene, aiMatrix4x4());
        }
    }
}