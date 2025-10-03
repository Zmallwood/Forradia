/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "text_renderer.hpp"
#include "core/core.hpp"

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
    auto sdl_color{text_color.to_sdl_color()};
    auto surf{TTF_RenderText_Solid(font_raw, text.data(), sdl_color)};
    size text_dim;
    TTF_SizeText(font_raw, text.data(), &text_dim.w, &text_dim.h);
    SDL_Rect dest_rect;
    auto canv_sz{get_canv_sz()};
    dest_rect.x = c_int(x * canv_sz.w);
    dest_rect.y = c_int(y * canv_sz.h);
    dest_rect.w = text_dim.w;
    dest_rect.h = text_dim.h;
    if (cent_align) {
      dest_rect.x -= dest_rect.w / 2;
      dest_rect.y -= dest_rect.h / 2;
    }
    auto rend{get_ston<sdl_device>().get_rend().get()};
    auto tex{SDL_CreateTextureFromSurface(rend, surf)};
    SDL_RenderCopy(rend, tex, nullptr, &dest_rect);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
  }
}