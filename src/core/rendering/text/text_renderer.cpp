/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "text_renderer.hpp"
#include "sub/create_fonts/create_fonts.hpp"
#include "sub/get_rendered_text_surface.hpp"
#include "sub/measure_rendered_text.hpp"
#include "sub/render_text_surface.hpp"

namespace forr {
  void text_renderer::Initialize() {
    TTF_Init();
    AddFonts();
  }

  void text_renderer::AddFonts() {
    m_fonts = forr::CreateFonts({font_sizes::_20, font_sizes::_26},
                                k_defaultFontPath);
  }

  void text_renderer::DrawString(str_view text, float x, float y,
                                 font_sizes fontSize, bool centerAlign,
                                 color textColor) const {
    auto fontRaw{m_fonts.at(fontSize).get()};
    auto surface{GetRenderedTextSurface(text, fontRaw, textColor)};
    auto textDimensions{MeasureRenderedText(text, fontRaw)};
    RenderTextSurface(surface, x, y, textDimensions, centerAlign);
    SDL_FreeSurface(surface);
  }
}