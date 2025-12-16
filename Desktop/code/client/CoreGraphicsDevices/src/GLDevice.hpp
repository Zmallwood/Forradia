//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

namespace Forradia {
/// Sets up the objects related to OpenGL.
class GLDevice {
 public:
  /// Default destructor.
  ~GLDevice();

  /// Initializes this device by setting up the GL functionality.
  void Initialize();

 private:
  /// Sets up the OpenGL context.
  void SetupGL();

  SharedPtr<SDL_GLContext> m_context; ///< The OpenGL context.
};
}