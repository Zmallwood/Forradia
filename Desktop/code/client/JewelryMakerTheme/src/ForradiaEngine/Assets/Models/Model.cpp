/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Model.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "ForradiaEngine/Common/Utilities.hpp"

namespace ForradiaEngine
{
    auto Model::initialize(std::string_view filePath) -> void
    {
        Assimp::Importer importer;

        unsigned int flags{aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
                           aiProcess_GenBoundingBoxes | aiProcess_FixInfacingNormals};

        // Read the model file.
        const aiScene *scene{importer.ReadFile(filePath.data(), flags)};

        If(nullptr == scene || nullptr == scene->mRootNode)
        {
            throwError("Assimp could not load model: " + std::string(importer.GetErrorString()));
        }
        Else
        {
            this->processNode(scene->mRootNode, scene, aiMatrix4x4());
        }
    }

    auto Model::processNode(aiNode *node, const aiScene *scene, aiMatrix4x4 transformation) -> void
    {
        // Iterate over all meshes in the node.
        Loop(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // Access the mesh.
            auto *mesh{scene->mMeshes[node->mMeshes[i]]};

            // Multiply the transformation with the node's transformation.
            transformation *= node->mTransformation;

            // Process the mesh.
            m_meshes.push_back(processMesh(mesh, scene, transformation));
        }

        // Iterate over all child nodes.
        Loop(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            // Process the child node (recursively).
            this->processNode(node->mChildren[i], scene, transformation);
        }
    }

    auto Model::processMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
        -> GLMMesh
    {
        If(mesh == nullptr)
        {
            throwError("mesh is nullptr");
        }

        If(scene == nullptr)
        {
            throwError("scene is nullptr");
        }

        auto vertices{Model::getVertices(mesh, transformation)};
        auto indices{Model::getIndices(mesh)};
        auto textures{Model::getTextures(mesh, scene)};

        return {vertices, indices, textures};
    }

    auto Model::getVertices(aiMesh *mesh, aiMatrix4x4 transformation) -> std::vector<GLMVertex>
    {
        If(mesh == nullptr)
        {
            throwError("mesh is nullptr");
        }

        std::vector<GLMVertex> vertices;

        // Iterate over all vertices.
        Loop(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            GLMVertex vertex;
            glm::vec3 position;

            // Get the transformed vertex position.
            auto verts{transformation * mesh->mVertices[i]};

            // Set the position coordinates.
            position.x = verts.x;
            position.y = verts.y;
            position.z = verts.z;

            vertex.position = position;

            // If there are normals.
            If(mesh->mNormals != nullptr)
            {
                glm::vec3 normal;

                // Set the normal coordinates.
                normal.x = mesh->mNormals[i].x;
                normal.y = mesh->mNormals[i].y;
                normal.z = mesh->mNormals[i].z;

                vertex.normal = normal;
            }

            // If there are texture coordinates.
            If(mesh->mTextureCoords[0] != nullptr)
            {
                glm::vec2 texCoords;

                // Set the texture coordinates.
                texCoords.x = mesh->mTextureCoords[0][i].x;
                texCoords.y = mesh->mTextureCoords[0][i].y;

                vertex.uv = texCoords;
            }
            else
            {
                // In case there are no texture coordinates, set them to zero.
                vertex.uv = glm::vec2(0, 0);
            }

            vertices.push_back(vertex);
        }
        return vertices;
    }

    auto Model::getIndices(aiMesh *mesh) -> std::vector<unsigned int>
    {
        If(mesh == nullptr)
        {
            throwError("mesh is null");
        }

        std::vector<unsigned int> indices;

        // Iterate over all faces.
        Loop(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            // Access the face.
            auto face{mesh->mFaces[i]};

            // Iterate over all indices in the face.
            Loop(unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        return indices;
    }

    auto Model::getTextures(aiMesh *mesh, const aiScene *scene) -> std::vector<Texture>
    {
        If(mesh == nullptr)
        {
            throwError("mesh is nullptr");
        }

        If(scene == nullptr)
        {
            throwError("scene is nullptr");
        }

        std::vector<Texture> textures;
        aiString textureFilePath;

        // Get the texture path.
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0,
                                                            &textureFilePath);
        // Add the texture to the results.
        textures.emplace_back(getFileNameNoExtension(textureFilePath.C_Str()));

        return textures;
    }
}
