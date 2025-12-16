/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/// A rendering operation for an image.
class Image2DRenderingOperation {
 public:
  GLuint vao; ///< The vertex array object.
  GLuint ibo; ///< The index buffer object.
  GLuint vbo; ///< The vertex buffer object.
};
}