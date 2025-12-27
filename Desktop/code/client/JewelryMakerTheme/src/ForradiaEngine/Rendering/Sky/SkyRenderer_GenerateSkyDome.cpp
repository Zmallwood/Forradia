/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

// TODO: Go through the comments and make sure they are correct.

#include "SkyRenderer.hpp"

#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

namespace ForradiaEngine
{
    auto SkyRenderer::generateSkyDome() -> void
    {
        // Generate a hemisphere (sky dome) mesh.

        // Number of horizontal segments (increased for better coverage).
        constexpr auto segments{64};

        // Number of vertical rings (increased for smoother dome).
        constexpr auto rings{32};

        std::vector<float> vertices;
        std::vector<unsigned short> indices;

        // Generate vertices.
        for (int ring = 0; ring <= rings; ++ring)
        {
            // Elevation angle (0 to PI/2).
            // NOLINTNEXTLINE(readability-magic-numbers)
            auto theta{ring * static_cast<float>(M_PI) / (2.0F * rings)};

            auto sinTheta{std::sin(theta)};
            auto cosTheta{std::cos(theta)};

            for (int segment = 0; segment <= segments; ++segment)
            {
                // Azimuth angle (0 to 2*PI).
                // NOLINTNEXTLINE(readability-magic-numbers)
                auto phi{segment * 2.0F * static_cast<float>(M_PI) / segments};

                auto sinPhi{std::sin(phi)};
                auto cosPhi{std::cos(phi)};

                // Calculate position on sphere.
                // Using standard spherical coordinates where:
                // - theta is elevation (0 = horizon, PI/2 = zenith)
                // - phi is azimuth (0 to 2*PI, full circle)
                // - Z is up (matches the game's coordinate system where +Z is vertical)

                auto xPos{cosPhi * sinTheta};
                auto yPos{sinPhi * sinTheta};

                // Z ranges from 1.0 (zenith) to 0.0 (horizon)
                auto zPos{cosTheta};

                // Store vertex position (3 floats).
                vertices.push_back(xPos);
                vertices.push_back(yPos);
                vertices.push_back(zPos);
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
                auto vert0{baseIndex + segment};
                auto vert1{baseIndex + segment + 1};

                // Next ring vertices.
                auto vert2{nextBaseIndex + segment};
                auto vert3{nextBaseIndex + segment + 1};

                // First triangle: v0 -> v2 -> v1 (counter-clockwise when viewed from outside).
                indices.push_back(vert0);
                indices.push_back(vert2);
                indices.push_back(vert1);

                // Second triangle: v1 -> v2 -> v3 (counter-clockwise when viewed from outside).
                indices.push_back(vert1);
                indices.push_back(vert2);
                indices.push_back(vert3);
            }
        }

        m_indexCount = static_cast<int>(indices.size());

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                     GL_STATIC_DRAW);

        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short),
                     indices.data(), GL_STATIC_DRAW);

        this->setupAttributeLayout();

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_initialized = true;
    }
}
