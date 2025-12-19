/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  class ShaderProgram;

  /**
   * Base class for all renderers.
   */
  class RendererBase {
   public:
    /**
     * Initialize the renderer with its shader program.
     */
    auto Initialize() -> void;

   protected:
    /**
     * Get the vertex shader source code.
     *
     * @return The vertex shader source code.
     */
    virtual auto GetVSSource() const -> std::string = 0;

    /**
     * Get the fragment shader source code.
     *
     * @return The fragment shader source code.
     */
    virtual auto GetFSSource() const -> std::string = 0;

    /**
     * Can be used to do additional initialization implemented in deriving class.
     */
    virtual auto InitializeDerived() -> void {
    }

    /**
     * Set up the attribute layout.
     */
    virtual auto SetupAttributeLayout() const -> void = 0;

    /**
     * Get the shader program.
     *
     * @return The shader program.
     */
    auto GetShaderProgram() const {
      return m_shaderProgram;
    }

   private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
  };
}
