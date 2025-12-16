//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "TextureBank.hpp"

namespace Forradia {
bool TextureBank::ObtainTextTexture(int uniqueTextureID, GLuint &textureID) {
  // Check if the text texture exists.
  if (m_textTextureIDs.contains(uniqueTextureID)) {
    textureID = m_textTextureIDs.at(uniqueTextureID);
    return true;
  }

  // If it doesn't, create it.
  glGenTextures(1, &textureID);
  m_textTextureIDs[uniqueTextureID] = textureID;
  return false;
}
}