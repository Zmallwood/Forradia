//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SkyRenderer.hpp"

#include "ShaderProgram.hpp"

namespace Forradia
{
    SkyRenderer::SkyRenderer() : m_vao{0}, m_ibo{0}, m_vbo{0}, m_indexCount{0}, m_initialized{false}
    {
        // Initialize the renderer base class.

        this->Initialize();
    }

    void SkyRenderer::Cleanup()
    {
        // Delete the vertex array object, index buffer object and vertex buffer object.

        if (m_vao != 0)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

        if (m_ibo != 0)
        {
            glDeleteBuffers(1, &m_ibo);
        }

        if (m_vbo != 0)
        {
            glDeleteBuffers(1, &m_vbo);
        }

        m_vao = 0;
        m_ibo = 0;
        m_vbo = 0;
        m_indexCount = 0;
        m_initialized = false;
    }

    void SkyRenderer::SetupState() const
    {
        // Get the canvas size and set the viewport.

        auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);

        // Use the shader program.

        glUseProgram(GetShaderProgram()->GetProgramID());

        // Enable depth testing with LEQUAL.
        // The sky vertices are set to far plane (z = w) in the vertex shader,
        // so they will render behind other geometry but fill empty space.

        glEnable(GL_DEPTH_TEST);

        glDepthFunc(GL_LEQUAL);

        // Disable depth writing so the sky doesn't occlude other objects.

        glDepthMask(GL_FALSE);

        // Disable face culling entirely to ensure all triangles render.
        // Since we're viewing from inside the dome, we need to see all faces.

        glDisable(GL_CULL_FACE);
    }

    void SkyRenderer::RestoreState() const
    {
        // Unbind the vertex array object, vertex buffer object and index buffer object.

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Restore depth writing.

        glDepthMask(GL_TRUE);

        // Disable depth testing.

        glDisable(GL_DEPTH_TEST);
    }

    void SkyRenderer::GenerateSkyDome()
    {
        // Generate a hemisphere (sky dome) mesh.

        const int segments{64}; // Number of horizontal segments (increased for better coverage).

        const int rings{32}; // Number of vertical rings (increased for smoother dome).

        Vector<float> vertices;

        Vector<unsigned short> indices;

        // Generate vertices.

        for (int ring = 0; ring <= rings; ++ring)
        {
            float theta{ring * M_PI / (2.0f * rings)}; // Elevation angle (0 to PI/2).

            float sinTheta{std::sin(theta)};

            float cosTheta{std::cos(theta)};

            for (int segment = 0; segment <= segments; ++segment)
            {
                float phi{segment * 2.0f * M_PI / segments}; // Azimuth angle (0 to 2*PI).

                float sinPhi{std::sin(phi)};

                float cosPhi{std::cos(phi)};

                // Calculate position on sphere.
                // Using standard spherical coordinates where:
                // - theta is elevation (0 = horizon, PI/2 = zenith)
                // - phi is azimuth (0 to 2*PI, full circle)
                // - Z is up (matches the game's coordinate system where +Z is vertical)

                float x{cosPhi * sinTheta};

                float y{sinPhi * sinTheta};

                float z{cosTheta};  // Z ranges from 1.0 (zenith) to 0.0 (horizon)

                // Store vertex position (3 floats).

                vertices.push_back(x);

                vertices.push_back(y);

                vertices.push_back(z);
            }
        }

        // Generate indices for the sky dome mesh.
        // Create triangles that form a complete 360-degree hemisphere.
        // Each quad (formed by two triangles) connects vertices in adjacent rings.

        for (int ring = 0; ring < rings; ++ring)
        {
            int baseIndex{ring * (segments + 1)};
            int nextBaseIndex{(ring + 1) * (segments + 1)};

            for (int segment = 0; segment < segments; ++segment)
            {
                // Current ring vertices.
                int v0{baseIndex + segment};
                int v1{baseIndex + segment + 1};

                // Next ring vertices.
                int v2{nextBaseIndex + segment};
                int v3{nextBaseIndex + segment + 1};

                // First triangle: v0 -> v2 -> v1 (counter-clockwise when viewed from outside).
                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v1);

                // Second triangle: v1 -> v2 -> v3 (counter-clockwise when viewed from outside).
                indices.push_back(v1);
                indices.push_back(v2);
                indices.push_back(v3);
            }
        }

        m_indexCount = static_cast<int>(indices.size());

        // Generate and bind vertex array object.

        glGenVertexArrays(1, &m_vao);

        glBindVertexArray(m_vao);

        // Generate and bind vertex buffer object.

        glGenBuffers(1, &m_vbo);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                     GL_STATIC_DRAW);

        // Generate and bind index buffer object.

        glGenBuffers(1, &m_ibo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short),
                     indices.data(), GL_STATIC_DRAW);

        // Setup attribute layout.

        this->SetupAttributeLayout();

        // Unbind.

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_initialized = true;
    }

    void SkyRenderer::Render(const glm::vec3 &sunDirection, float sunElevation)
    {
        // Generate the sky dome mesh if not already initialized.

        if (!m_initialized)
        {
            this->GenerateSkyDome();
        }

        // Set up the state for the renderer.

        this->SetupState();

        // Bind the vertex array object.

        glBindVertexArray(m_vao);

        // Calculate the MVP matrix.
        // The sky should always be centered on the camera and scaled to be far away.

        auto modelMatrix{glm::mat4(1.0f)};

        // Scale the sky dome to be within the camera's far plane but still large enough.
        // Camera far plane is 100.0, so we use a radius slightly less than that.
        // We'll scale it to be at the far plane (depth = 1.0 in NDC) regardless of actual distance.

        float skyRadius{90.0f}; // Within the far plane of 100.0

        modelMatrix = glm::scale(modelMatrix, glm::vec3(skyRadius, skyRadius, skyRadius));

        // Translate the sky dome down along the Z axis to lower it.
        // Since we remove translation from the view matrix, this translation happens
        // in view space, effectively lowering the sky in the camera's view.
        // Negative Z moves it down (since +Z is up in this coordinate system).

        float skyOffsetZ{-0.5f}; // Adjust this value to control how much to lower the sky

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, skyOffsetZ));

        auto viewMatrix{_<Camera>().GetViewMatrix()};

        // For sky rendering, extract only the rotation part of the view matrix.
        // The view matrix from glm::lookAt has translation in the 4th column.
        // We want to keep the rotation (upper-left 3x3) but remove translation.
        
        // Create identity matrix and copy rotation elements.
        glm::mat4 viewMatrixRotationOnly{1.0f};
        
        // Copy rotation part (upper-left 3x3) from view matrix.
        // In GLM: matrix[column][row], so we copy columns 0-2, rows 0-2.
        viewMatrixRotationOnly[0] = glm::vec4(viewMatrix[0].x, viewMatrix[0].y, viewMatrix[0].z, 0.0f);
        viewMatrixRotationOnly[1] = glm::vec4(viewMatrix[1].x, viewMatrix[1].y, viewMatrix[1].z, 0.0f);
        viewMatrixRotationOnly[2] = glm::vec4(viewMatrix[2].x, viewMatrix[2].y, viewMatrix[2].z, 0.0f);
        viewMatrixRotationOnly[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        auto projectionMatrix{_<Camera>().GetProjectionMatrix()};

        auto mvpMatrix{projectionMatrix * viewMatrixRotationOnly * modelMatrix};

        // Upload the MVP matrix to the shader.

        glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

        // Upload the sun direction to the shader.

        glUniform3fv(m_layoutLocationSunDirection, 1, &sunDirection[0]);

        // Upload the sun elevation to the shader.

        glUniform1f(m_layoutLocationSunElevation, sunElevation);

        // Draw the sky dome.

        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, nullptr);

        // Restore the state.

        this->RestoreState();
    }

    void SkyRenderer::SetupAttributeLayout() const
    {
        // Set up the attribute layout for the vertex shader.
        // Position (3 floats).

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

        glEnableVertexAttribArray(0);
    }

    void SkyRenderer::InitializeDerived()
    {
        // Get the layout locations for the uniforms.

        m_layoutLocationMVP = glGetUniformLocation(GetShaderProgram()->GetProgramID(), "MVP");

        m_layoutLocationSunDirection =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "sunDirection");

        m_layoutLocationSunElevation =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "sunElevation");

        // Check if uniform locations are valid (should not be -1).

        if (m_layoutLocationMVP == -1 || m_layoutLocationSunDirection == -1 ||
            m_layoutLocationSunElevation == -1)
        {
            // Uniform locations not found - shader might have compilation errors.
            // This will be visible when trying to render.
        }
    }
}