/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Sets up the OpenGL context and the OpenGL functions.
 */
class GLDevice {
 public:
  /**
   * Default destructor.
   */
  ~GLDevice();

  /**
   * Initializes this device by setting up the GL functionality.
   */
  void Initialize();

 private:
  void SetupGL();

  SharedPtr<SDL_GLContext> m_context;
};
}