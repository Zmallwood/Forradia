//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GroundRenderingOperation.hpp"

namespace Forradia
{
    class ShaderProgram;

    class GroundRenderer
    {
      public:
        GroundRenderer()
        {
            Initialize();
        };

        ~GroundRenderer()
        {
            Cleanup();
        }

        void DrawTile(int imageNameHash, int xCoordinate,
                      int yCoordinate, float tileSize,
                      Point3F cameraPosition,
                      Vector<float> &elevations,
                      float elevationHeight);

        void DrawTexture(GLuint textureID,
                         Vector<float> &vertices,
                         Point3F cameraPosition);

      private:
        void Initialize();

        void Cleanup();

        String GetVertexShaderSource() const;

        String GetFragmentShaderSource() const;

        glm::vec3 ComputeNormal(glm::vec3 p1, glm::vec3 p2,
                                glm::vec3 p3);

        SharedPtr<ShaderProgram> m_shaderProgram;

        std::map<
            float,
            std::map<
                float,
                std::map<GLuint, GroundRenderingOperation>>>
            m_operationsMemory;
    };
}