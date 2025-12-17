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
  GLuint GetTexture(int imageNameHash) const;

  /**
   * Gets the dimensions of a texture with the given hash.
   *
   * @param imageNameHash The hash of the image name.
   * @return The dimensions of the texture.
   */
  Size GetTextureDimensions(int imageNameHash) const;

  /**
   * Obtains a text texture ID for the given unique texture ID.
   *
   * @param uniqueTextureID The unique texture ID.
   * @param[out] textureID The texture ID (output parameter).
   * @return True if the texture was found, false otherwise.
   */
  bool ObtainTextTexture(int uniqueTextureID, GLuint &textureID);

 private:
  void Initialize();

  void Cleanup();

  void LoadTextures();

  GLuint LoadSingleTexture(SharedPtr<SDL_Surface> surface) const;

  inline static const String k_relativeImagesPath{"./Resources/Images/"};
  std::map<int, TextureEntry> m_textureEntries;
  std::map<int, GLuint> m_textTextureIDs;
};
}