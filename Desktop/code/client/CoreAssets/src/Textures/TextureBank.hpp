/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "TextureEntry.hpp"

struct SDL_Surface;

namespace Forradia {
/**
 * Manages loading and providing of textures which are being used in opengl rendering.
 */
class TextureBank {
 public:
  /**
   * Constructor.
   */
  TextureBank() {
    this->Initialize();
  }

  /**
   * Destructor.
   */
  ~TextureBank() {
    this->Cleanup();
  }

  /**
   * Get a texture ID for the given image name hash.
   *
   * @param imageNameHash The hash of the image name.
   * @return The texture ID.
   */
  auto GetTexture(int imageNameHash) const -> GLuint;

  /**
   * Gets the dimensions of a texture with the given hash.
   *
   * @param imageNameHash The hash of the image name.
   * @return The dimensions of the texture.
   */
  auto GetTextureDimensions(int imageNameHash) const -> Size;

  /**
   * Obtains a text texture ID for the given unique texture ID.
   *
   * @param uniqueTextureID The unique texture ID.
   * @param[out] textureID The texture ID (output parameter).
   * @return True if the texture was found, false otherwise.
   */
  auto ObtainTextTexture(int uniqueTextureID, GLuint &textureID) -> bool;

 private:
  auto Initialize() -> void;

  auto Cleanup() -> void;

  auto LoadTextures() -> void;

  auto LoadSingleTexture(SharedPtr<SDL_Surface> surface) const -> GLuint;

  inline static const String k_relativeImagesPath{"./Resources/Images/"};
  std::map<int, TextureEntry> m_textureEntries;
  std::map<int, GLuint> m_textTextureIDs;
};
}
