/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "RendererBase.hpp"
    
    #include "ForradiaEngine/Rendering/Base/ShaderProgram.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto RendererBase::initialize() -> void
    {
        auto vertexShaderSource{this->getVSSource()};
        auto fragmentShaderSource{this->getFSSource()};

        m_shaderProgram = std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

        this->initializeDerived();
    }
}
