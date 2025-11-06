//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIPlayerStatusBox.hpp"

#include "TextRenderer.hpp"

#include "PlayerCharacter.hpp"

namespace Forradia::Theme0
{
    void GUIPlayerStatusBox::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        _<TextRenderer>().DrawString(
            k_renderIDNameString,
            _<Theme0::GameplayCore::PlayerCharacter>()
                .GetName(),
            bounds.x + 0.01f, bounds.y + 0.01f,
            FontSizes::_26);
    }
}