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
  void text_renderer::initialize() {
    TTF_Init();
    add_fonts();
  }

  void text_renderer::add_fonts() {
    m_fonts = forr::create_fonts({font_sizes::_20, font_sizes::_26},
                                 k_defaultFontPath);
  }

  void text_renderer::draw_string(str_view text, float x, float y,
                                  font_sizes fontSize, bool centerAlign,
                                  color textColor) const {
    auto fontRaw{m_fonts.at(fontSize).get()};
    auto surface{get_rendered_text_surface(text, fontRaw, textColor)};
    auto textDimensions{measure_rendered_text(text, fontRaw)};
    render_text_surface(surface, x, y, textDimensions, centerAlign);
    SDL_FreeSurface(surface);
  }
}