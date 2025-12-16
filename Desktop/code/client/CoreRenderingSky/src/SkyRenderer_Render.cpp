//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:
// - Go through the comments and make sure they are correct.

#include "SkyRenderer.hpp"

namespace Forradia {
    void SkyRenderer::Render(const glm::vec3 &sunDirection, float sunElevation) {
        if (!m_initialized) {
            this->GenerateSkyDome();
        }

        this->SetupState();

        glBindVertexArray(m_vao);

        // Calculate the MVP matrix.
        // The sky should always be centered on the camera and scaled to be far away.

        auto modelMatrix{glm::mat4(1.0f)};

        // Scale the sky dome to be within the camera's far plane but still large enough.
        // Camera far plane is 100.0, so we use a radius slightly less than that.
        // We'll scale it to be at the far plane (depth = 1.0 in NDC) regardless of actual
        // distance.

        // Within the far plane of 100.0

        auto skyRadius{90.0f};

        modelMatrix = glm::scale(modelMatrix, glm::vec3(skyRadius, skyRadius, skyRadius));

        // Translate the sky dome down along the Z axis to lower it.
        // Since we remove translation from the view matrix, this translation happens
        // in view space, effectively lowering the sky in the camera's view.
        // Negative Z moves it down (since +Z is up in this coordinate system).

        // Adjust this value to control how much to lower the sky
        auto skyOffsetZ{-0.5f};

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, skyOffsetZ));

        auto viewMatrix{_<Camera>().GetViewMatrix()};

        // For sky rendering, extract only the rotation part of the view matrix.
        // The view matrix from glm::lookAt has translation in the 4th column.
        // We want to keep the rotation (upper-left 3x3) but remove translation.

        // Create identity matrix and copy rotation elements.

        glm::mat4 viewMatrixRotationOnly{1.0f};

        // Copy rotation part (upper-left 3x3) from view matrix.
        // In GLM: matrix[column][row], so we copy columns 0-2, rows 0-2.

        viewMatrixRotationOnly[0] =
            glm::vec4(viewMatrix[0].x, viewMatrix[0].y, viewMatrix[0].z, 0.0f);

        viewMatrixRotationOnly[1] =
            glm::vec4(viewMatrix[1].x, viewMatrix[1].y, viewMatrix[1].z, 0.0f);

        viewMatrixRotationOnly[2] =
            glm::vec4(viewMatrix[2].x, viewMatrix[2].y, viewMatrix[2].z, 0.0f);

        viewMatrixRotationOnly[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        auto projectionMatrix{_<Camera>().GetProjectionMatrix()};

        auto mvpMatrix{projectionMatrix * viewMatrixRotationOnly * modelMatrix};

        // Upload the MVP matrix to the shader.
        glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

        // Upload the sun direction to the shader.
        glUniform3fv(m_layoutLocationSunDirection, 1, &sunDirection[0]);

        // Upload the sun elevation to the shader.
        glUniform1f(m_layoutLocationSunElevation, sunElevation);

        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, nullptr);

        this->RestoreState();
    }
}