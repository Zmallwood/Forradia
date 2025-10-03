/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "rend.hpp"
#include "engine.hpp"

namespace forr {
  void image_renderer::draw_img(str_view img_name, float x, float y, float w,
                                float h) const {
    draw_img(hash(img_name), x, y, w, h);
  }

  void image_renderer::draw_img(int img_name_hash, float x, float y, float w,
                                float h) const {
    auto img{_<image_bank>().get_img(img_name_hash)};
    auto c_sz{canv_sz(_<sdl_device>().win())};
    auto x_px{c_int(x * c_sz.w)};
    auto y_px{c_int(y * c_sz.h)};
    auto w_px{c_int(w * c_sz.w)};
    auto h_px{c_int(h * c_sz.h)};
    SDL_Rect sdl_rect{x_px, y_px, w_px, h_px};
    SDL_RenderCopy(_<sdl_device>().rend().get(), img.get(), nullptr,
                   &sdl_rect);
  }

  void image_renderer::draw_img_auto_h(str_view img_name, float x, float y,
                                       float w) const {
    auto img_name_hash{hash(img_name)};
    auto img_sz{_<image_bank>().get_img_sz(img_name_hash)};
    auto canv_asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
    auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
    auto h{w / img_asp_rat * canv_asp_rat};
    draw_img(hash(img_name), x, y, w, h);
  }

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
      fonts_.insert({font_sz, new_font});
    }
  }

  void text_renderer::draw_str(str_view text, float x, float y,
                               font_sizes font_sz, bool cent_align,
                               color text_color) const {
    auto font_raw{fonts_.at(font_sz).get()};
    auto sdl_color{text_color.to_sdl_color()};
    auto surf{TTF_RenderText_Solid(font_raw, text.data(), sdl_color)};
    sz text_dim;
    TTF_SizeText(font_raw, text.data(), &text_dim.w, &text_dim.h);
    SDL_Rect dest_rect;
    auto c_sz{canv_sz(_<sdl_device>().win())};
    dest_rect.x = c_int(x * c_sz.w);
    dest_rect.y = c_int(y * c_sz.h);
    dest_rect.w = text_dim.w;
    dest_rect.h = text_dim.h;
    if (cent_align) {
      dest_rect.x -= dest_rect.w / 2;
      dest_rect.y -= dest_rect.h / 2;
    }
    auto rend{_<sdl_device>().rend().get()};
    auto tex{SDL_CreateTextureFromSurface(rend, surf)};
    SDL_RenderCopy(rend, tex, nullptr, &dest_rect);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
  }
}