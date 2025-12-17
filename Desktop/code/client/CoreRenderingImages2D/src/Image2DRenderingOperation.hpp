/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * A rendering operation for an image.
 */
class Image2DRenderingOperation {
 public:
  /**
   * The vertex array object.
   */
  GLuint vao;

  /**
   * The index buffer object.
   */
  GLuint ibo;

  /**
   * The vertex buffer object.
   */
  GLuint vbo;
};
}