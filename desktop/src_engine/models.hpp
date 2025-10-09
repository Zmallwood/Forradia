/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class vertex {
   public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
  };

  class texture {
   public:
    str path_;
  };

  class mesh {
   public:
    vec<vertex> vertices;
    vec<unsigned int> indices;
    vec<texture> textures;
    glm::vec3 extents;
    glm::vec3 origin;
    aiString name;
  };

  class model {
   public:
    model(str_view file_path) { init(file_path); };

    auto &meshes_ref() const { return meshes_; }

   private:
    void init(str_view file_path);

    void process_node(aiNode *node, const aiScene *scene,
                      aiMatrix4x4 transform);

    mesh process_mesh(aiMesh *mesh, const aiScene *scene,
                      aiMatrix4x4 transformation);

    vec<vertex> get_vertices(aiMesh *mesh, glm::vec3 &extents,
                             glm::vec3 &origin, aiMatrix4x4 transformation);

    vec<unsigned int> get_indices(aiMesh *mesh);

    vec<texture> get_textures(aiMesh *mesh, const aiScene *scene);

    vec<mesh> meshes_;
  };
}