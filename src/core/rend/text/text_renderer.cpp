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
                                 k_default_font_path);
  }

  void text_renderer::draw_string(str_view text, float x, float y,
                                  font_sizes font_size, bool center_align,
                                  color text_color) const {
    auto font_raw{m_fonts.at(font_size).get()};
    auto surface{get_rendered_text_surface(text, font_raw, text_color)};
    auto text_dimensions{measure_rendered_text(text, font_raw)};
    render_text_surface(surface, x, y, text_dimensions, center_align);
    SDL_FreeSurface(surface);
  }
}