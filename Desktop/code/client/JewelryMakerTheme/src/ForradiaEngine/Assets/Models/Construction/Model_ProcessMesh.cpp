/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
#include "Model.hpp"

namespace Forradia
{
    auto Model::processMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
        -> GLMMesh
    {
        if (mesh == nullptr)
        {
            throwError("mesh is nullptr");
        }

        if (scene == nullptr)
        {
            throwError("scene is nullptr");
        }

        auto vertices{Model::getVertices(mesh, transformation)};
        auto indices{Model::getIndices(mesh)};
        auto textures{Model::getTextures(mesh, scene)};

        return {vertices, indices, textures};
    }
}
