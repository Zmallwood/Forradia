/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_renderer.hpp"
#include "core/core.hpp"

namespace forr {
  void image_renderer::draw_img(str_view img_name, float x, float y, float w,
                                float h) const {
    draw_img(hash(img_name), x, y, w, h);
  }

  void image_renderer::draw_img(int img_name_hash, float x, float y, float w,
                                float h) const {
    auto img{get_ston<image_bank>().get_img(img_name_hash)};
    auto canv_sz{get_canv_sz()};
    auto x_px{c_int(x * canv_sz.w)};
    auto y_px{c_int(y * canv_sz.h)};
    auto w_px{c_int(w * canv_sz.w)};
    auto h_px{c_int(h * canv_sz.h)};
    SDL_Rect sdl_rect{x_px, y_px, w_px, h_px};
    SDL_RenderCopy(get_ston<sdl_device>().get_rend().get(), img.get(), nullptr,
                   &sdl_rect);
  }

  void image_renderer::draw_img_auto_h(str_view img_name, float x, float y,
                                       float w) const {
    auto img_name_hash{hash(img_name)};
    auto img_sz{get_ston<image_bank>().get_img_sz(img_name_hash)};
    auto canv_asp_rat{calc_aspect_ratio()};
    auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
    auto h{w / img_asp_rat * canv_asp_rat};
    draw_img(hash(img_name), x, y, w, h);
  }
}