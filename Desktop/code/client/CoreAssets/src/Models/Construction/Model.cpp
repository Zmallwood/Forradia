/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Model.hpp"
#include "ErrorUtilities.hpp"
#include "MessageUtilities.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace Forradia {
    auto Model::Initialize(std::string_view filePath) -> void {
        Assimp::Importer importer;
        unsigned int flags{aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
                           aiProcess_GenBoundingBoxes | aiProcess_FixInfacingNormals};

        // Read the model file.
        const aiScene *scene{importer.ReadFile(filePath.data(), flags)};

        if (nullptr == scene || nullptr == scene->mRootNode)
            PrintError("Assimp could not load model: " + std::string(importer.GetErrorString()));
        else
            this->ProcessNode(scene->mRootNode, scene, aiMatrix4x4());
    }
}
