//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Model.hpp"

namespace Forradia
{
    GLMMesh Model::ProcessMesh(aiMesh *mesh,
                               const aiScene *scene,
                               aiMatrix4x4 transformation)
    {
        // Get the mesh's vertices.

        auto vertices{
            this->GetVertices(mesh, transformation)};

        // Get the mesh's indices.

        auto indices{this->GetIndices(mesh)};

        // Get the mesh's textures.

        auto textures{this->GetTextures(mesh, scene)};

        // Create and return a mesh (non-assimp type)
        // object.

        return GLMMesh(vertices, indices, textures);
    }
}