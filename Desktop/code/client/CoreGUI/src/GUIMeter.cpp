//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIMeter.hpp"

#include "Color2DRenderer.hpp"

namespace Forradia
{
    void GUIMeter::RenderDerived() const
    {
        auto bounds{GetBounds()};

        //std::cout << "bounds: " << bounds.x << ", " << bounds.y << ", " << bounds.width << ", "
        //          << bounds.height << std::endl;
        // Render the background.

        _<Color2DRenderer>().DrawFilledRectangle(
            k_renderIDBackground, Palette::GetColor<Hash("Black")>(), GetBounds().x, GetBounds().y,
            GetBounds().width, GetBounds().height);

        // Render the filled part.

        _<Color2DRenderer>().DrawFilledRectangle(
            k_renderIDFilled, m_filledColor, GetBounds().x, GetBounds().y,
            GetBounds().width * m_filledPercentage, GetBounds().height);
    }
}