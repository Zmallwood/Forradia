/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include <memory>

using SDL_GLContext = void *;

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
    auto Initialize() -> void;

   private:
    auto SetupGL() -> void;

    std::shared_ptr<SDL_GLContext> m_context;
  };
}
