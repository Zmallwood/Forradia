//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIMeter.hpp"
#include "Color2DRenderer.hpp"

namespace Forradia {
    void GUIMeter::RenderDerived() const {
        auto bounds{GetBounds()};

        _<Color2DRenderer>().DrawFilledRectangle(
            k_renderIDBackground, Palette::GetColor<Hash("Black")>(), GetBounds().x, GetBounds().y,
            GetBounds().width, GetBounds().height);
        _<Color2DRenderer>().DrawFilledRectangle(
            k_renderIDFilled, k_filledColor, GetBounds().x, GetBounds().y,
            GetBounds().width * GetFilledPercentage(), GetBounds().height, true);
    }
}