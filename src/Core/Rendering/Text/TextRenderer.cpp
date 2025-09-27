/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "TextRenderer.hpp"
#include "Sub/CreateFonts.hpp"
#include "Sub/GetRenderedTextSurface.hpp"
#include "Sub/MeasureRenderedText.hpp"
#include "Sub/RenderTextSurface.hpp"

namespace Forradia
{
    TextRenderer::TextRenderer()
    {
        TTF_Init();

        AddFonts();
    }

    void TextRenderer::AddFonts()
    {
        m_fonts = Forradia::CreateFonts({FontSizes::_20,
                                         FontSizes::_26},
                                        k_defaultFontPath);
    }

    void TextRenderer::DrawString(StringView text,
                                  float x,
                                  float y,
                                  FontSizes fontSize,
                                  bool centerAlign,
                                  Color textColor) const
    {
        auto fontRaw{m_fonts.at(fontSize).get()};

        auto surface{GetRenderedTextSurface(text, fontRaw, textColor)};

        auto textDimensions{MeasureRenderedText(text, fontRaw)};

        RenderTextSurface(surface, x, y, textDimensions, centerAlign);

        SDL_FreeSurface(surface);
    }
}