//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "SkyRenderer.hpp"

namespace Forradia
{
    void SkyRenderer::GenerateSkyDome()
    {
        // Generate a hemisphere (sky dome) mesh.

        // Number of horizontal segments (increased for better coverage).

        const auto segments{64};

        // Number of vertical rings (increased for smoother dome).

        const auto rings{32};

        Vector<float> vertices;

        Vector<unsigned short> indices;

        // Generate vertices.

        for (int ring = 0; ring <= rings; ++ring)
        {
            // Elevation angle (0 to PI/2).

            auto theta{ring * static_cast<float>(M_PI) / (2.0f * rings)};

            auto sinTheta{std::sin(theta)};

            auto cosTheta{std::cos(theta)};

            for (int segment = 0; segment <= segments; ++segment)
            {
                // Azimuth angle (0 to 2*PI).

                auto phi{segment * 2.0f * static_cast<float>(M_PI) / segments};

                auto sinPhi{std::sin(phi)};

                auto cosPhi{std::cos(phi)};

                // Calculate position on sphere.
                // Using standard spherical coordinates where:
                // - theta is elevation (0 = horizon, PI/2 = zenith)
                // - phi is azimuth (0 to 2*PI, full circle)
                // - Z is up (matches the game's coordinate system where +Z is vertical)

                auto x{cosPhi * sinTheta};

                auto y{sinPhi * sinTheta};

                // Z ranges from 1.0 (zenith) to 0.0 (horizon)

                auto z{cosTheta};

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
            auto baseIndex{ring * (segments + 1)};

            auto nextBaseIndex{(ring + 1) * (segments + 1)};

            for (int segment = 0; segment < segments; ++segment)
            {
                // Current ring vertices.

                auto v0{baseIndex + segment};

                auto v1{baseIndex + segment + 1};

                // Next ring vertices.

                auto v2{nextBaseIndex + segment};

                auto v3{nextBaseIndex + segment + 1};

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
}