/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "TextRenderer.hpp"
#include "Sub/AddFonts.hpp"
#include "Sub/GetRenderedTextSurface.hpp"
#include "Sub/MeasureRenderedText.hpp"
#include "Sub/CreateRenderDestinationRect.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    TextRenderer::TextRenderer()
    {
        TTF_Init();

        AddFonts();
    }

    void TextRenderer::AddFonts()
    {
        m_fonts = Forradia::AddFonts({FontSizes::_20,
                                      FontSizes::_26},
                                     k_defaultFontPath);
    }

    void TextRenderer::DrawString(std::string_view text,
                                  float x,
                                  float y,
                                  FontSizes fontSize,
                                  bool centerAlign,
                                  Color textColor) const
    {
        auto fontRaw{m_fonts.at(fontSize).get()};

        auto surface{GetRenderedTextSurface(text, fontRaw, textColor)};

        auto textDimensions{MeasureRenderedText(text, fontRaw)};

        auto renderer{_<SDLDevice>().GetRenderer().get()};

        auto texture{
            SDL_CreateTextureFromSurface(renderer, surface)};

        auto destinationRect{CreateRenderDestinationRect(x, y, textDimensions, centerAlign)};

        SDL_RenderCopy(renderer, texture, nullptr, &destinationRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}