//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIPanel.hpp"

#include "Engine.hpp"

namespace Forradia
{
    void GUIPanel::RenderDerived() const
    {
        auto bounds{this->GetBounds()};

        _<Engine::Renderers::Image2DRenderer>().DrawImage(
            m_backgroundImage, bounds.x, bounds.y,
            bounds.width, bounds.height);
    }
}