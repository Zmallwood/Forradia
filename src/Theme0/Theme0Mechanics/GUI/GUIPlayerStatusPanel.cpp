/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIPlayerStatusPanel.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"

namespace Forradia
{
    GUIPlayerStatusPanel::GUIPlayerStatusPanel()
    : GUIPanel( 0.0f, 0.0f, 0.2f, 0.14f )
    {}

    void GUIPlayerStatusPanel::RenderDerived() const
    {
        GUIPanel::RenderDerived();
        
        auto bounds { GetBounds() };
        
        _<TextRenderer>().DrawString(
            _<Player>().GetName(),
            bounds.x + 0.01f,
            bounds.y + 0.01f,
            FontSizes::_26
        );
    }
}