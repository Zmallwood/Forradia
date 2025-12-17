/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Image2DRenderingOperation.hpp"
#include "RendererBase.hpp"

namespace Forradia {
/**
 * A renderer for drawing images to the canvas.
 */
class Image2DRenderer : public RendererBase {
 public:
  /**
   * Destructor which cleans up the renderer.
   */
  ~Image2DRenderer() {
    // Clean up the renderer.
    this->Cleanup();
  }

  /**
   * Draws an image by name.
   *
   * @param uniqueRenderID The unique render ID.
   * @param imageName The name of the image.
   * @param x The x coordinate of the image.
   * @param y The y coordinate of the image.
   * @param width The width of the image.
   * @param height The height of the image.
   * @param updateExisting Whether to update the existing operation.
   */
  auto DrawImageByName(int uniqueRenderID, StringView imageName, float x, float y, float width,
                       float height, bool updateExisting = false) -> void;

  /**
   * Draws an image by hash.
   *
   * @param uniqueRenderID The unique render ID.
   * @param imageNameHash The hash of the image name.
   * @param x The x coordinate of the image.
   * @param y The y coordinate of the image.
   * @param width The width of the image.
   * @param height The height of the image.
   * @param updateExisting Whether to update the existing operation.
   */
  auto DrawImageByHash(int uniqueRenderID, int imageNameHash, float x, float y, float width,
                       float height, bool updateExisting = false) -> void;

  /**
   * Draws an image by texture ID.
   *
   * @param uniqueRenderID The unique render ID.
   * @param textureID The texture ID.
   * @param x The x coordinate of the image.
   * @param y The y coordinate of the image.
   * @param width The width of the image.
   * @param height The height of the image.
   * @param updateExisting Whether to update the existing operation.
   */
  auto DrawImageByTextureID(int uniqueRenderID, GLuint textureID, float x, float y, float width,
                            float height, bool updateExisting = false) -> void;

  /**
   * Draws an image by name with automatic height, meaning the height is calculated based
   * on the width and the aspect ratio of the image.
   *
   * @param uniqueRenderID The unique render ID.
   * @param imageName The name of the image.
   * @param x The x coordinate of the image.
   * @param y The y coordinate of the image.
   * @param width The width of the image.
   * @param height The height of the image.
   */
  auto DrawImageAutoHeight(int uniqueRenderID, StringView imageName, float x, float y, float width)
      -> void;

 protected:
  /**
   * Returns the vertex shader source.
   *
   * @return The vertex shader source.
   */
  auto GetVSSource() const -> String override;

  /**
   * Returns the fragment shader source.
   *
   * @return The fragment shader source.
   */
  auto GetFSSource() const -> String override;

  /**
   * Sets up the attribute layout.
   */
  auto SetupAttributeLayout() const -> void override;

 private:
  auto Cleanup() -> void;

  auto SetupState() const -> void;

  auto RestoreState() const -> void;

  auto DrawingOperationIsCached(int uniqueRenderID) const -> bool;

  std::map<int, Image2DRenderingOperation> m_operationsCache;
};
}
