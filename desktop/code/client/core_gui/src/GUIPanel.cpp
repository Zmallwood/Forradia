//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIPanel.hpp"

#include "Images2D/Image2DRenderer.hpp"

namespace Forradia
{
    void GUIPanel::RenderDerived() const
    {
        auto bounds{this->GetBounds()};

        _<Image2DRenderer>().DrawImageByName(
            m_backgroundImage, bounds.x, bounds.y,
            bounds.width, bounds.height);
    }
}