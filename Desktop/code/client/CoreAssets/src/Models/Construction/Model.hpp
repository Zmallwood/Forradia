/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/GLMTypes/GLMMesh.hpp"
#include "assimp/scene.h"

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
        Model(std::string_view filePath) {
            this->Initialize(filePath);
        };

        /**
         * Returns a reference to the model's meshes.
         *
         * @return A reference to the model's meshes.
         */
        [[nodiscard]] auto GetMeshesRef() const -> const std::vector<GLMMesh> & {
            return m_meshes;
        }

      private:
        auto Initialize(std::string_view filePath) -> void;

        auto ProcessNode(aiNode *node, const aiScene *scene, aiMatrix4x4 transform) -> void;

        static auto ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
            -> GLMMesh;

        static auto GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) -> std::vector<GLMVertex>;

        static auto GetIndices(aiMesh *mesh) -> std::vector<unsigned int>;

        static auto GetTextures(aiMesh *mesh, const aiScene *scene) -> std::vector<Texture>;

        std::vector<GLMMesh> m_meshes;
    };
}
