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
            std::cout << "ERROR::ASSIMP Could not load "
                         "model: "
                      << importer.GetErrorString()
                      << std::endl;
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

            // Only apply transformation on meshes not
            // entities such as lights or camera.
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

    Vector<GLMVertex>
    Model::GetVertices(aiMesh *mesh,
                       aiMatrix4x4 transformation)
    {
        Vector<GLMVertex> vertices;

        for (unsigned int i = 0; i < mesh->mNumVertices;
             i++)
        {
            GLMVertex vertex;

            glm::vec3 vector3;

            aiVector3D v{transformation *
                         mesh->mVertices[i]};

            // Vertices.
            vector3.x = v.x;
            vector3.y = v.y;
            vector3.z = v.z;

            vertex.position = vector3;

            // Normals.
            if (mesh->mNormals)
            {
                vector3.x = mesh->mNormals[i].x;
                vector3.y = mesh->mNormals[i].y;
                vector3.z = mesh->mNormals[i].z;

                vertex.normal = vector3;
            }

            // Texture coordinates.
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vector2;

                vector2.x = mesh->mTextureCoords[0][i].x;
                vector2.y = mesh->mTextureCoords[0][i].y;

                vertex.uv = vector2;
            }
            else
            {
                vertex.uv = glm::vec2(0, 0);
            }

            vertices.push_back(vertex);
        }

        return vertices;
    }

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

    Vector<Texture> Model::GetTextures(aiMesh *mesh,
                                       const aiScene *scene)
    {
        Vector<Texture> textures;

        aiString s;

        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(
            aiTextureType_DIFFUSE, 0, &s);

        textures.push_back(
            Texture(GetFileNameNoExtension(s.C_Str())));

        return textures;
    }
}