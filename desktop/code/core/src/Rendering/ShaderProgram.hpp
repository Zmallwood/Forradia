//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class ShaderProgram
    {
      public:
        ShaderProgram(StringView vertexShaderSource,
                      StringView fragmentShaderSource)
        {
            Initialize(vertexShaderSource,
                       fragmentShaderSource);
        }

        ~ShaderProgram()
        {
            Cleanup();
        }

        auto GetProgramID() const
        {
            return m_programID;
        }

      private:
        void Initialize(StringView vertexShaderSource,
                        StringView fragmentShaderSource);

        void Cleanup();

        GLuint m_programID;
    };
}