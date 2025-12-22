/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "RendererBase.hpp"
#include "ShaderProgram.hpp"

namespace Forradia
{
    auto RendererBase::Initialize() -> void
    {
        auto vertexShaderSource{this->GetVSSource()};
        auto fragmentShaderSource{this->GetFSSource()};

        m_shaderProgram = std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

        this->InitializeDerived();
    }
}
