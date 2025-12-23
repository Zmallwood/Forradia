/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "RendererBase.hpp"
#include <glm/vec3.hpp>
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia
{
    /**
        A renderer for procedurally rendering the sky.
     */
    class SkyRenderer : public RendererBase
    {
      public:
        static auto instance() -> SkyRenderer &
        {
            static SkyRenderer instance;
            return instance;
        }

        // Delete copy/move
        SkyRenderer(const SkyRenderer &) = delete;

        auto operator=(const SkyRenderer &) -> SkyRenderer & = delete;

        /**
            Constructor.
         */
        SkyRenderer()
        {
            // Initialize the renderer base class.
            dynamic_cast<RendererBase *>(this)->initialize();
        }

        /**
            Destructor that cleans up the renderer.
         */
        ~SkyRenderer() override
        {
            // Cleanup the renderer.
            this->cleanup();
        }

        /**
            Renders the sky dome.

            @note This should be called FIRST, before rendering any other 3D geometry,

            @param sunDirection The direction vector of the sun (should be normalized).
            @param sunElevation The elevation angle of the sun in radians (0 = horizon, PI/2 =
            zenith). Negative values indicate nighttime (darker sky).
         */
        auto render(const glm::vec3 &sunDirection, float sunElevation) -> void;

      protected:
        /**
            Returns the vertex shader source.

            @return The vertex shader source.
         */
        [[nodiscard]] auto getVSSource() const -> std::string override;

        /**
            Returns the fragment shader source.

            @return The fragment shader source.
         */
        [[nodiscard]] auto getFSSource() const -> std::string override;

        /**
            Does initialization that is specific to this renderer.
         */
        auto initializeDerived() -> void override;

        /**
            Sets up the attribute layout for the vertex shader.
         */
        auto setupAttributeLayout() const -> void override;

      private:
        auto cleanup() -> void;

        auto setupState() const -> void;

        static auto restoreState() -> void;

        auto generateSkyDome() -> void;

        GLuint m_vao{};
        GLuint m_ibo{};
        GLuint m_vbo{};
        int m_indexCount{};
        GLint m_layoutLocationMVP{};
        GLint m_layoutLocationSunDirection{};
        GLint m_layoutLocationSunElevation{};
        bool m_initialized{false};
    };
}
