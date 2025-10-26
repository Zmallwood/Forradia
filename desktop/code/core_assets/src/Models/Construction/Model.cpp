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
        Assimp::Importer importer;

        const aiScene *scene{importer.ReadFile(
            filePath.data(),
            aiProcess_Triangulate | aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace |
                aiProcess_GenBoundingBoxes |
                aiProcess_FixInfacingNormals)};

        if (!scene || !scene->mRootNode)
        {
            PrintLine(
                "ERROR: ASSIMP could not load model: " +
                String(importer.GetErrorString()));
        }
        else
        {
            this->ProcessNode(scene->mRootNode, scene,
                              aiMatrix4x4());
        }
    }

    void Model::ProcessNode(aiNode *node,
                            const aiScene *scene,
                            aiMatrix4x4 transformation)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh{scene->mMeshes[node->mMeshes[i]]};

            transformation *= node->mTransformation;

            m_meshes.push_back(
                ProcessMesh(mesh, scene, transformation));
        }

        for (unsigned int i = 0; i < node->mNumChildren;
             i++)
        {
            this->ProcessNode(node->mChildren[i], scene,
                              transformation);
        }
    }

    GLMMesh Model::ProcessMesh(aiMesh *mesh,
                               const aiScene *scene,
                               aiMatrix4x4 transformation)
    {
        Vector<GLMVertex> vertices{
            this->GetVertices(mesh, transformation)};

        Vector<unsigned int> indices{
            this->GetIndices(mesh)};

        Vector<Texture> textures{
            this->GetTextures(mesh, scene)};

        return GLMMesh(vertices, indices, textures);
    }
}