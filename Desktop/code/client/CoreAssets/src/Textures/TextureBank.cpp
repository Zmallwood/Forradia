/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "TextureBank.hpp"

namespace Forradia {
  auto TextureBank::Initialize() -> void {
    TextureBank::LoadTextures();
  }

  auto TextureBank::Cleanup() -> void {
    for (auto entry : m_textureEntries)
      glDeleteTextures(1, &entry.second.textureID);
    for (auto entry : m_textTextureIDs)
      glDeleteTextures(1, &entry.second);
    m_textureEntries.clear();
    m_textTextureIDs.clear();
  }

  auto TextureBank::GetTexture(int imageNameHash) -> GLuint {
    if (m_textureEntries.contains(imageNameHash))
      return m_textureEntries.at(imageNameHash).textureID;
    return -1;
  }

  auto TextureBank::GetTextureDimensions(int imageNameHash) -> Size {
    if (m_textureEntries.contains(imageNameHash))
      return m_textureEntries.at(imageNameHash).dimensions;
    return {-1, -1};
  }
}
