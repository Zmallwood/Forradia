/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIMeter.hpp"
    #include "ForradiaEngine/Rendering/Colors/Color2DRenderer.hpp"
    #include "ForradiaEngine/Common/Matter/Coloring/Palette.hpp"
// clang-format on

namespace Forradia
{
    auto GUIMeter::renderDerived() const -> void
    {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};

        Color2DRenderer::instance().drawFilledRectangle(
            k_renderIDBackground, Palette::getColor<hash("DarkGray")>(), bounds.x, bounds.y,
            bounds.width, bounds.height);
        Color2DRenderer::instance().drawFilledRectangle(
            k_renderIDFilled, k_filledColor, bounds.x, bounds.y,
            bounds.width * getFilledPercentage(), bounds.height, true);

        Color2DRenderer::instance().drawLine(
            k_renderIDLineTop, Palette::getColor<hash("WheatTransparent")>(), bounds.x, bounds.y,
            bounds.x + bounds.width, bounds.y, k_borderWidth);

        Color2DRenderer::instance().drawLine(
            k_renderIDLineBottom, Palette::getColor<hash("WheatTransparent")>(), bounds.x,
            bounds.y + bounds.height, bounds.x + bounds.width, bounds.y + bounds.height,
            k_borderWidth);

        Color2DRenderer::instance().drawLine(
            k_renderIDLineRight, Palette::getColor<hash("WheatTransparent")>(),
            bounds.x + bounds.width, bounds.y, bounds.x + bounds.width, bounds.y + bounds.height,
            k_borderWidth);

        Color2DRenderer::instance().drawLine(
            k_renderIDLineLeft, Palette::getColor<hash("WheatTransparent")>(), bounds.x, bounds.y,
            bounds.x, bounds.y + bounds.height, k_borderWidth);
    }
}
