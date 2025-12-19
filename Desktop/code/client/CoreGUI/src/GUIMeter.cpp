/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIMeter.hpp"
#include "Color2DRenderer.hpp"

namespace Forradia {
  auto GUIMeter::RenderDerived() const -> void {
    auto bounds{GetBounds()};

    _<Color2DRenderer>().DrawFilledRectangle(k_renderIDBackground,
                                             Palette::GetColor<Hash("DarkGray")>(), GetBounds().x,
                                             GetBounds().y, GetBounds().width, GetBounds().height);
    _<Color2DRenderer>().DrawFilledRectangle(
        k_renderIDFilled, k_filledColor, GetBounds().x, GetBounds().y,
        GetBounds().width * GetFilledPercentage(), GetBounds().height, true);

    _<Color2DRenderer>().DrawLine(k_renderIDLineTop, Palette::GetColor<Hash("WheatTransparent")>(),
                                  bounds.x, bounds.y, bounds.x + bounds.width, bounds.y, 0.002f);

    _<Color2DRenderer>().DrawLine(
        k_renderIDLineBottom, Palette::GetColor<Hash("WheatTransparent")>(), bounds.x,
        bounds.y + bounds.height, bounds.x + bounds.width, bounds.y + bounds.height, 0.002f);

    _<Color2DRenderer>().DrawLine(
        k_renderIDLineRight, Palette::GetColor<Hash("WheatTransparent")>(), bounds.x + bounds.width,
        bounds.y, bounds.x + bounds.width, bounds.y + bounds.height, 0.002f);

    _<Color2DRenderer>().DrawLine(k_renderIDLineLeft, Palette::GetColor<Hash("WheatTransparent")>(),
                                  bounds.x, bounds.y, bounds.x, bounds.y + bounds.height, 0.002f);
  }
}
