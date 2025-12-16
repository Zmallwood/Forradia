//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIPanel.hpp"
#include "Image2DRenderer.hpp"

namespace Forradia {
    void GUIPanel::RenderDerived() const {
        // Get the bounds of this panel.

        auto bounds{this->GetBounds()};

        // Draw the background image of this panel.

        _<Image2DRenderer>().DrawImageByName(k_renderIDBackground, m_backgroundImage, bounds.x,
                                             bounds.y, bounds.width, bounds.height, true);
    }
}