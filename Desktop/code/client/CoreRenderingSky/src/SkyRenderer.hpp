/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "RendererBase.hpp"

namespace Forradia {
  /**
   * A renderer for procedurally rendering the sky.
   */
  class SkyRenderer : public RendererBase {
   public:
    /**
     * Constructor.
     */
    SkyRenderer() : m_vao{0}, m_ibo{0}, m_vbo{0}, m_indexCount{0}, m_initialized{false} {
      // Initialize the renderer base class.
      this->Initialize();
    }

    /**
     * Destructor that cleans up the renderer.
     */
    ~SkyRenderer() {
      // Cleanup the renderer.
      this->Cleanup();
    }

    /**
     * Renders the sky dome.
     *
     * @note This should be called FIRST, before rendering any other 3D geometry,
     *
     * @param sunDirection The direction vector of the sun (should be normalized).
     * @param sunElevation The elevation angle of the sun in radians (0 = horizon, PI/2 =
     * zenith). Negative values indicate night time (darker sky).
     */
    auto Render(const glm::vec3 &sunDirection, float sunElevation) -> void;

   protected:
    /**
     * Returns the vertex shader source.
     *
     * @return The vertex shader source.
     */
    auto GetVSSource() const -> String override;

    /**
     * Returns the fragment shader source.
     *
     * @return The fragment shader source.
     */
    auto GetFSSource() const -> String override;

    /**
     * Does initialization that is specific to this renderer.
     */
    auto InitializeDerived() -> void override;

    /**
     * Sets up the attribute layout for the vertex shader.
     */
    auto SetupAttributeLayout() const -> void override;

   private:
    auto Cleanup() -> void;

    auto SetupState() const -> void;

    auto RestoreState() const -> void;

    auto GenerateSkyDome() -> void;

    GLuint m_vao;
    GLuint m_ibo;
    GLuint m_vbo;
    int m_indexCount;
    GLint m_layoutLocationMVP;
    GLint m_layoutLocationSunDirection;
    GLint m_layoutLocationSunElevation;
    bool m_initialized;
  };
}
