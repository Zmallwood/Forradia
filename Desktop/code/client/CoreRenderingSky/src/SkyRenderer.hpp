//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

#include "RendererBase.hpp"

namespace Forradia
{
    /// A renderer for procedurally rendering the sky.
    class SkyRenderer : public RendererBase
    {
      public:
        /// Constructor.
        SkyRenderer() : m_vao{0}, m_ibo{0}, m_vbo{0}, m_indexCount{0}, m_initialized{false}
        {
            // Initialize the renderer base class.
            this->Initialize();
        }

        /// Destructor that cleans up the renderer.
        ~SkyRenderer()
        {
            // Cleanup the renderer.
            this->Cleanup();
        }

        /// Renders the sky dome.
        ///
        /// @note This should be called FIRST, before rendering any other 3D geometry,
        ///       to ensure the sky appears as the background.
        ///
        /// @param sunDirection The direction vector of the sun (should be normalized).
        /// @param sunElevation The elevation angle of the sun in radians (0 = horizon, PI/2 =
        /// zenith). Negative values indicate night time (darker sky).
        void Render(const glm::vec3 &sunDirection, float sunElevation);

      protected:
        /// Returns the vertex shader source.
        ///
        /// @return The vertex shader source.
        String GetVSSource() const override;

        /// Returns the fragment shader source.
        ///
        /// @return The fragment shader source.
        String GetFSSource() const override;

        /// Does initialization that is specific to this renderer.
        void InitializeDerived() override;

        /// Sets up the attribute layout for the vertex shader.
        void SetupAttributeLayout() const override;

      private:
        /// Cleans up the renderer.
        void Cleanup();

        /// Sets up the state for the renderer.
        void SetupState() const;

        /// Restores the state for the renderer.
        void RestoreState() const;

        /// Generates the sky dome mesh vertices and indices.
        void GenerateSkyDome();

        GLuint m_vao; ///< The vertex array object.

        GLuint m_ibo; ///< The index buffer object.

        GLuint m_vbo; ///< The vertex buffer object.

        int m_indexCount; ///< The number of indices in the sky dome.

        GLint m_layoutLocationMVP; ///< Layout location for the MVP matrix in the shader.

        GLint m_layoutLocationSunDirection; ///< Layout location for the sun direction in the
                                            ///< shader.

        GLint m_layoutLocationSunElevation; ///< Layout location for the sun elevation in the
                                            ///< shader.

        bool m_initialized; ///< Whether the sky dome mesh has been initialized.
    };
}