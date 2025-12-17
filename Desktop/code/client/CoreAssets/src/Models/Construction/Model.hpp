/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Holds information about a model, used by the ModelBank.
 */
class Model {
 public:
  /**
   * Constructor.
   *
   * @param filePath The path to the model file.
   */
  Model(StringView filePath) {
    this->Initialize(filePath);
  };

  /**
   * Returns a reference to the model's meshes.
   *
   * @return A reference to the model's meshes.
   */
  auto &GetMeshesRef() const {
    return m_meshes;
  }

 private:
  void Initialize(StringView filePath);

  void ProcessNode(aiNode *node, const aiScene *scene, aiMatrix4x4 transform);

  GLMMesh ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation) const;

  Vector<GLMVertex> GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) const;

  Vector<unsigned int> GetIndices(aiMesh *mesh) const;

  Vector<Texture> GetTextures(aiMesh *mesh, const aiScene *scene) const;

  Vector<GLMMesh> m_meshes;
};
}