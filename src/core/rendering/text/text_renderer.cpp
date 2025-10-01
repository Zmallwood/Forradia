/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "text_renderer.hpp"
#include "sub/get_rendered_text_surface.hpp"
#include "sub/measure_rendered_text.hpp"
#include "sub/render_text_surface.hpp"
#include "sub/create_fonts/create_fonts.hpp"

namespace forr {
  void TextRenderer::Initialize() {
    TTF_Init();
    AddFonts();
  }

  void TextRenderer::AddFonts() {
    m_fonts = forr::CreateFonts({FontSizes::_20, FontSizes::_26},
                                    k_defaultFontPath);
  }

  void TextRenderer::DrawString(StringView text, float x, float y,
                                FontSizes fontSize, bool centerAlign,
                                Color textColor) const {
    auto fontRaw{m_fonts.at(fontSize).get()};
    auto surface{GetRenderedTextSurface(text, fontRaw, textColor)};
    auto textDimensions{MeasureRenderedText(text, fontRaw)};
    RenderTextSurface(surface, x, y, textDimensions, centerAlign);
    SDL_FreeSurface(surface);
  }
}