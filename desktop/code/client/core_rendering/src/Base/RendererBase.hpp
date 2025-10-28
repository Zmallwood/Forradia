//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class ShaderProgram;

    class RendererBase
    {
      public:
        void Initialize();

      protected:
        auto GetShaderProgram() const
        {
            return m_shaderProgram;
        }

        virtual String GetVSSource() const = 0;

        virtual String GetFSSource() const = 0;

      private:
        SharedPtr<ShaderProgram> m_shaderProgram;
    };
}