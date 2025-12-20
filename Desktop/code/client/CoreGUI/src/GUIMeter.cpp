/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIMeter.hpp"
#include "Color2DRenderer.hpp"
#include "Coloring/Palette.hpp"
#include "Singleton.hpp"

namespace Forradia {
    auto GUIMeter::RenderDerived() const -> void {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->GetBounds()};

        _<Color2DRenderer>().DrawFilledRectangle(k_renderIDBackground,
                                                 Palette::GetColor<Hash("DarkGray")>(), bounds.x,
                                                 bounds.y, bounds.width, bounds.height);
        _<Color2DRenderer>().DrawFilledRectangle(k_renderIDFilled, k_filledColor, bounds.x,
                                                 bounds.y, bounds.width * GetFilledPercentage(),
                                                 bounds.height, true);

        _<Color2DRenderer>().DrawLine(k_renderIDLineTop,
                                      Palette::GetColor<Hash("WheatTransparent")>(), bounds.x,
                                      bounds.y, bounds.x + bounds.width, bounds.y, k_borderWidth);

        _<Color2DRenderer>().DrawLine(k_renderIDLineBottom,
                                      Palette::GetColor<Hash("WheatTransparent")>(), bounds.x,
                                      bounds.y + bounds.height, bounds.x + bounds.width,
                                      bounds.y + bounds.height, k_borderWidth);

        _<Color2DRenderer>().DrawLine(k_renderIDLineRight,
                                      Palette::GetColor<Hash("WheatTransparent")>(),
                                      bounds.x + bounds.width, bounds.y, bounds.x + bounds.width,
                                      bounds.y + bounds.height, k_borderWidth);

        _<Color2DRenderer>().DrawLine(k_renderIDLineLeft,
                                      Palette::GetColor<Hash("WheatTransparent")>(), bounds.x,
                                      bounds.y, bounds.x, bounds.y + bounds.height, k_borderWidth);
    }
}
