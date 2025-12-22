/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"
#include "Model.hpp"

namespace Forradia
{
    auto Model::ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
        -> GLMMesh
    {
        if (mesh == nullptr)
        {
            ThrowError("mesh is nullptr");
        }

        if (scene == nullptr)
        {
            ThrowError("scene is nullptr");
        }

        auto vertices{Model::GetVertices(mesh, transformation)};
        auto indices{Model::GetIndices(mesh)};
        auto textures{Model::GetTextures(mesh, scene)};
        return {vertices, indices, textures};
    }
}
