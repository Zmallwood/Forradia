//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Holds information about a model, used by the ModelBank.
    ///
    class Model
    {
      public:
        ///
        /// Constructor
        ///
        /// @param filePath The path to the model file.
        ///
        Model(StringView filePath)
        {
            this->Initialize(filePath);
        };

        ///
        /// Returns a reference to the model's meshes.
        ///
        /// @return A reference to the model's meshes.
        ///
        auto &GetMeshesRef() const
        {
            return m_meshes;
        }

      private:
        ///
        /// Initializes the model by completely loading it from a file into a number of GLMMesh
        /// objects.
        ///
        /// @param filePath The path to the model file.
        ///
        void Initialize(StringView filePath);

        ///
        /// Processes a node in the model.
        ///
        /// @param node The node to process.
        /// @param scene The scene the node is in.
        /// @param transform The resulting transformation of the node, with regards to its parent
        /// nodes.
        ///
        void ProcessNode(aiNode *node, const aiScene *scene, aiMatrix4x4 transform);

        ///
        /// Processes a mesh in the model.
        ///
        /// @param mesh The mesh to process.
        /// @param scene The scene the mesh is in.
        /// @param transformation The resulting transformation that should be applied to the mesh,
        /// with regards to its parent nodes.
        /// @return The processed mesh as a GLMMesh (non-assimp type) object.
        ///
        GLMMesh ProcessMesh(aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation) const;

        ///
        /// Gets the vertices of a mesh.
        ///
        /// @param mesh The mesh to get the vertices of.
        /// @param transformation The transformation that should be applied to the vertices of the
        /// mesh.
        /// @return The vertices of the mesh.
        ///
        Vector<GLMVertex> GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) const;

        ///
        /// Gets the indices of a mesh.
        ///
        /// @param mesh The mesh to get the indices of.
        /// @return The indices of the mesh.
        ///
        Vector<unsigned int> GetIndices(aiMesh *mesh) const;

        ///
        /// Gets the textures of a mesh.
        ///
        /// @param mesh The mesh to get the textures of.
        /// @param scene The scene the mesh is in.
        /// @return The textures of the mesh.
        ///
        Vector<Texture> GetTextures(aiMesh *mesh, const aiScene *scene) const;

        Vector<GLMMesh> m_meshes; ///< The model's meshes.
    };
}