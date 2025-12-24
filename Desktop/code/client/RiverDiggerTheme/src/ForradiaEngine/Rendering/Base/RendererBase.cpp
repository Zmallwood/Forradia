/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "RendererBase.hpp"
#include "ShaderProgram.hpp"

namespace Forradia
{
    auto RendererBase::initialize() -> void
    {
        auto vertexShaderSource{this->getVSSource()};
        auto fragmentShaderSource{this->getFSSource()};

        m_shaderProgram = std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

        this->initializeDerived();
    }
}
