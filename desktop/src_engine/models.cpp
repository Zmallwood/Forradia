/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "models.hpp"

namespace forr {
  void model::init(str_view file_path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
        file_path.data(), aiProcess_Triangulate | aiProcess_FlipUVs |
                              aiProcess_CalcTangentSpace |
                              aiProcess_GenBoundingBoxes);

    if (!scene || !scene->mRootNode) {
      std::cout << "ERROR::ASSIMP Could not load model: "
                << importer.GetErrorString() << std::endl;
    } else {
      std::cout << "Init model: " << file_path << std::endl;
      //      this->directory = filename.substr(0, filename.find_last_of('/'));
      //
      process_node(scene->mRootNode, scene, aiMatrix4x4());
    }
  }

  void model::process_node(aiNode *node, const aiScene *scene,
                           aiMatrix4x4 transformation) {
    std::cout << "process node\n";
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

      // only apply transformation on meshs not entities such as lights or
      // camera.
      transformation *= node->mTransformation;

      meshes_.push_back(process_mesh(mesh, scene, transformation));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
      process_node(node->mChildren[i], scene, transformation);
    }
  }

  mesh model::process_mesh(aiMesh *mesh, const aiScene *scene,
                           aiMatrix4x4 transformation) {
    std::cout << "process mesh\n";
    glm::vec3 extents;
    glm::vec3 origin;

    std::vector<vertex> vertices =
        get_vertices(mesh, extents, origin, transformation);
    std::vector<unsigned int> indices = get_indices(mesh);
    std::vector<texture> textures = get_textures(mesh, scene);

    return forr::mesh(vertices, indices, textures, extents, origin,
                      mesh->mName);
  }

  vec<vertex> model::get_vertices(aiMesh *mesh, glm::vec3 &extents,
                                  glm::vec3 &origin,
                                  aiMatrix4x4 transformation) {
    std::cout << "get vertices\n";
    std::vector<vertex> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      forr::vertex vertex;

      glm::vec3 vector3;

      aiVector3D v = transformation * mesh->mVertices[i];

      // Vertices
      vector3.x = v.x;
      vector3.y = v.y;
      vector3.z = v.z;

      vertex.position = vector3;

      // Normals
      if (mesh->mNormals) {
        vector3.x = mesh->mNormals[i].x;
        vector3.y = mesh->mNormals[i].y;
        vector3.z = mesh->mNormals[i].z;
        vertex.normal = vector3;
      }

      // Texture coordinates
      if (mesh->mTextureCoords[0]) {
        glm::vec2 vector2;

        vector2.x = mesh->mTextureCoords[0][i].x;
        vector2.y = mesh->mTextureCoords[0][i].y;
        vertex.tex_coord = vector2;
      } else {
        vertex.tex_coord = glm::vec2(0, 0);
      }

      if (mesh->mTangents) {
        vector3.x = mesh->mTangents[i].x;
        vector3.y = mesh->mTangents[i].y;
        vector3.z = mesh->mTangents[i].z;
        vertex.tangent = vector3;
      }

      // Bitangent
      if (mesh->mBitangents) {
        vector3.x = mesh->mBitangents[i].x;
        vector3.y = mesh->mBitangents[i].y;
        vector3.z = mesh->mBitangents[i].z;
        vertex.bitangent = vector3;
      }

      vertices.push_back(vertex);
    }

    glm::vec3 min =
        glm::vec3(mesh->mAABB.mMin.x, mesh->mAABB.mMin.y, mesh->mAABB.mMin.z);
    glm::vec3 max =
        glm::vec3(mesh->mAABB.mMax.x, mesh->mAABB.mMax.y, mesh->mAABB.mMax.z);

    extents = (max - min) * 0.5f;
    origin = glm::vec3((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f,
                       (min.z + max.z) / 2.0f);

    printf("%f,%f,%f\n", origin.x, origin.y, origin.z);

    return vertices;
  }

  vec<unsigned int> model::get_indices(aiMesh *mesh) {
    std::cout << "get indices\n";
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }
    return indices;
  }

  vec<texture> model::get_textures(aiMesh *mesh, const aiScene *scene) {
    std::cout << "get textures\n";
    std::vector<texture> textures;
    for (unsigned int i = 0; i < scene->mNumTextures; i++) {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
      aiString path;
      material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
      textures.push_back(texture(path.C_Str()));
    }
    return textures;
  }
}