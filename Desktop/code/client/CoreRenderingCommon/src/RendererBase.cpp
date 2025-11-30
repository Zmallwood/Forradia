//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "RendererBase.hpp"

#include "ShaderProgram.hpp"

namespace AAK
{
    namespace Forradia
    {
        void RendererBase::Initialize()
        {
            // Get vertex shader source, implemented in deriving class.

            String vertexShaderSource{this->GetVSSource()};

            // Get fragment shader source, implemented in deriving class.

            String fragmentShaderSource{this->GetFSSource()};

            // Create the shader program.

            m_shaderProgram =
                std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

            // Do additional initialization, implemented in deriving class.

            this->InitializeDerived();
        }
    }
}