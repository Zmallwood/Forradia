//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "RendererBase.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
    void RendererBase::Initialize() {
        String vertexShaderSource{this->GetVSSource()};
        String fragmentShaderSource{this->GetFSSource()};
        m_shaderProgram = std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
        this->InitializeDerived();
    }
}