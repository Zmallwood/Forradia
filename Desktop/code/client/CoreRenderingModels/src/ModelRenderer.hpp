/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "ModelRenderingOperation.hpp"
#include "RendererBase.hpp"

namespace Forradia {
/**
 * This renderer is used to render models from the model bank in 3D space.
 */
class ModelRenderer : public RendererBase {
 public:
  /**
   * Destructor that cleans up the renderer.
   */
  ~ModelRenderer() {
    // Clean up the renderer.
    this->Cleanup();
  }

  /**
   * Draws a model in 3D space.
   *
   * @param modelNameHash The hash of the model to draw.
   * @param x The x coordinate of the model.
   * @param y The y coordinate of the model.
   * @param elevations The elevations of the tile where the model is located.
   * @param modelScaling The scaling of the model.
   */
  void DrawModel(int modelNameHash, float x, float y, float elevations, float modelScaling = 1.0f);

 protected:
  /**
   * Gets the vertex shader source.
   *
   * @return The vertex shader source.
   */
  String GetVSSource() const override;

  /**
   * Gets the fragment shader source.
   *
   * @return The fragment shader source.
   */
  String GetFSSource() const override;

  /**
   * Additional initialization for this derived class.
   */
  void InitializeDerived() override;

  /**
   * Sets up the attribute layout.
   */
  void SetupAttributeLayout() const override;

 private:
  void Cleanup();

  void SetupState() const;

  void RestoreState() const;

  bool DrawingOperationIsCached(int modelNameHash) const;

  static constexpr float k_globalModelScaling{0.5f};
  std::map<int, ModelRenderingOperation> m_operationsCache;
  GLint m_layoutLocationProjectionMatrix;
  GLint m_layoutLocationViewMatrix;
  GLint m_layoutLocationModelMatrix;
};
}