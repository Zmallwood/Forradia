/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"

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
    [[nodiscard]] auto GetMeshesRef() const -> const Vector<GLMMesh> & {
      return m_meshes;
    }

   private:
    auto Initialize(StringView filePath) -> void;

    auto ProcessNode(aiNode *node, const aiScene *scene, aiMatrix4x4 transform) -> void;

    auto ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation) const
        -> GLMMesh;

    auto GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) const -> Vector<GLMVertex>;

    auto GetIndices(aiMesh *mesh) const -> Vector<unsigned int>;

    auto GetTextures(aiMesh *mesh, const aiScene *scene) const -> Vector<Texture>;

    Vector<GLMMesh> m_meshes;
  };
}
