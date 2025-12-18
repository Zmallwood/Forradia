/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Model.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto Model::ProcessNode(aiNode *node, const aiScene *scene, aiMatrix4x4 transformation) -> void {
    // Iterate over all meshes in the node.
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      // Access the mesh.
      auto mesh{scene->mMeshes[node->mMeshes[i]]};

      // Multiply the transformation with the node's transformation.
      transformation *= node->mTransformation;

      // Process the mesh.
      m_meshes.push_back(ProcessMesh(mesh, scene, transformation));
    }

    // Iterate over all child nodes.
    for (unsigned int i = 0; i < node->mNumChildren; i++)
      // Process the child node (recursively).
      this->ProcessNode(node->mChildren[i], scene, transformation);
  }
}
