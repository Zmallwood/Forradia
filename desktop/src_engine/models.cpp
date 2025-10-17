/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "models.hpp"

namespace forr {
  void model::init(str_view file_path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
        file_path.data(),
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
            aiProcess_GenBoundingBoxes | aiProcess_FixInfacingNormals);
    if (!scene || !scene->mRootNode) {
      std::cout << "ERROR::ASSIMP Could not load model: "
                << importer.GetErrorString() << std::endl;
    } else {
      process_node(scene->mRootNode, scene, aiMatrix4x4());
    }
    // std::cout << "TEXXXX: "<< scene->mTextures[0]->mFilename.C_Str() <<
    // std::endl;
  }

  void model::process_node(aiNode *node, const aiScene *scene,
                           aiMatrix4x4 transformation) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      // Only apply transformation on meshes not entities such as lights or
      // camera.
      transformation *= node->mTransformation;
      meshes_.push_back(process_mesh(mesh, scene, transformation));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
      process_node(node->mChildren[i], scene, transformation);
  }

  mesh model::process_mesh(aiMesh *mesh, const aiScene *scene,
                           aiMatrix4x4 transformation) {
    glm::vec3 extents;
    glm::vec3 origin;
    vec<vertex> vertices = get_vertices(mesh, extents, origin, transformation);
    vec<unsigned int> indices = get_indices(mesh);
    vec<texture> textures = get_textures(mesh, scene);
    return forr::mesh(vertices, indices, textures, extents, origin,
                      mesh->mName);
  }

  vec<vertex> model::get_vertices(aiMesh *mesh, glm::vec3 &extents,
                                  glm::vec3 &origin,
                                  aiMatrix4x4 transformation) {
    vec<vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      forr::vertex vertex;
      glm::vec3 vector3;
      aiVector3D v = transformation * mesh->mVertices[i];
      // Vertices.
      vector3.x = v.x;
      vector3.y = v.y;
      vector3.z = v.z;
      vertex.position = vector3;
      // Normals.
      if (mesh->mNormals) {
        vector3.x = mesh->mNormals[i].x;
        vector3.y = mesh->mNormals[i].y;
        vector3.z = mesh->mNormals[i].z;
        vertex.normal = vector3;
      }
      // Texture coordinates.
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
      // Bitangent.
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
    return vertices;
  }

  vec<unsigned int> model::get_indices(aiMesh *mesh) {
    vec<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }
    return indices;
  }

  vec<texture> model::get_textures(aiMesh *mesh, const aiScene *scene) {
    vec<texture> textures;

    //std::cout << " NUM MATERIALS: " << scene->mNumMaterials << std::endl;
    aiString s;
    scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &s);
    textures.push_back(texture(file_name_no_ext(s.C_Str())));
//    for (unsigned int i = 0; i < scene->mNumTextures; i++) {
//      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
//      aiString path;
//      material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
//      // material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), path);
//      std::cout << "NUM TEXES: " << scene->mNumTextures << std::endl;
//      if ('*' == path.data[0]) {
//        // embedded texture, get index from string and access scene->mTextures
//        std::cout << "embedded texture" << std::endl;
//        auto mat{scene->mMaterials[atoi(&path.data[1])]};
//        mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
//      }
//      textures.push_back(texture(path.C_Str()));
//      std::cout << "TEX: " << path.C_Str() << std::endl;
//      scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &path);
//      std::cout << path.C_Str() << std::endl;
//    }
    return textures;
  }
}