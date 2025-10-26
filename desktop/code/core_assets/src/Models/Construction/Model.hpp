//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class Model
    {
      public:
        Model(StringView filePath)
        {
            Initialize(filePath);
        };

        auto &GetMeshesRef() const
        {
            return m_meshes;
        }

      private:
        void Initialize(StringView filePath);

        void ProcessNode(aiNode *node, const aiScene *scene,
                         aiMatrix4x4 transform);

        GLMMesh ProcessMesh(aiMesh *mesh,
                            const aiScene *scene,
                            aiMatrix4x4 transformation);

        Vector<GLMVertex>
        GetVertices(aiMesh *mesh,
                    aiMatrix4x4 transformation);

        Vector<unsigned int> GetIndices(aiMesh *mesh);

        Vector<Texture> GetTextures(aiMesh *mesh,
                                    const aiScene *scene);

        Vector<GLMMesh> m_meshes;
    };
}