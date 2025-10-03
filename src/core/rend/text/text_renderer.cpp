/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "text_renderer.hpp"
#include "sub/get_rend_text_surf.hpp"
#include "sub/measure_rend_text.hpp"
#include "sub/rend_text_surf.hpp"

namespace forr {
  void text_renderer::init() {
    TTF_Init();
    add_fonts();
  }

  void text_renderer::add_fonts() {
    auto abs_font_path{str(SDL_GetBasePath()) + k_default_font_path.data()};
    for (auto font_sz : {font_sizes::_20, font_sizes::_26}) {
      auto font_path_unix_style{repl(abs_font_path, '\\', '/')};
      auto font_sz_n{c_int(font_sz)};
      auto new_font{s_ptr<TTF_Font>(
          TTF_OpenFont(font_path_unix_style.c_str(), font_sz_n), sdl_del())};
      if (!new_font) {
        print_ln("Error loading font.");
        return;
      }
      m_fonts.insert({font_sz, new_font});
    }
  }

  void text_renderer::draw_str(str_view text, float x, float y,
                               font_sizes font_sz, bool cent_align,
                               color text_color) const {
    auto font_raw{m_fonts.at(font_sz).get()};
    auto surf{get_rend_text_surf(text, font_raw, text_color)};
    auto text_dim{measure_rend_text(text, font_raw)};
    rend_text_surf(surf, x, y, text_dim, cent_align);
    SDL_FreeSurface(surf);
  }
}