//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIMeter.hpp"
#include "Color2DRenderer.hpp"

namespace AAK
{
    namespace Forradia
    {
        void GUIMeter::RenderDerived() const
        {
            auto bounds{GetBounds()};

            // Render the background.

            _<Color2DRenderer>().DrawFilledRectangle(
                k_renderIDBackground, Palette::GetColor<Hash("Black")>(), GetBounds().x,
                GetBounds().y, GetBounds().width, GetBounds().height);

            // Render the filled part.

            _<Color2DRenderer>().DrawFilledRectangle(
                k_renderIDFilled, k_filledColor, GetBounds().x, GetBounds().y,
                GetBounds().width * GetFilledPercentage(), GetBounds().height, true);
        }
    }
}