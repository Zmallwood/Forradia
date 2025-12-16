/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/// Holds information about a texture, used by the TextureBank.
class TextureEntry {
 public:
  GLuint textureID; ///< The texture ID, used by opengl.
  Size dimensions;  ///< The texture width and height.
};
}