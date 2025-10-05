/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "rend.hpp"
#include "engine.hpp"

namespace forr {
  void img_rend::draw_img(str_view img_name, float x, float y, float w,
                          float h) const {
    draw_img(hash(img_name), x, y, w, h);
  }

  void img_rend::draw_img(int img_name_hash, float x, float y, float w,
                          float h) const {

    // glEnable(GL_TEXTURE_2D);
    // glEnable(GL_BLEND);                                // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function
    glBindTexture(GL_TEXTURE_2D, _<image_bank>().get_tex(img_name_hash));
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, 0.5f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + w, y, 0.5f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + w, y + h, 0.5f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y + h, 0.5f);

    glEnd();
    glFlush();
    return;
    auto img{_<image_bank>().get_img(img_name_hash)};
    auto canv_sz{get_canv_sz(_<sdl_device>().win())};
    auto x_px{c_int(x * canv_sz.w)};
    auto y_px{c_int(y * canv_sz.h)};
    auto w_px{c_int(w * canv_sz.w)};
    auto h_px{c_int(h * canv_sz.h)};
    SDL_Rect rect{x_px, y_px, w_px, h_px};
    SDL_RenderCopy(_<sdl_device>().rend().get(), img.get(), nullptr, &rect);
  }

  void img_rend::draw_img_auto_h(str_view img_name, float x, float y,
                                 float w) const {
    auto hash{forr::hash(img_name)};
    auto img_sz{_<image_bank>().get_img_sz(hash)};
    if (img_sz.w <= 0 || img_sz.h <= 0)
      return;
    auto canv_asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
    auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
    auto h{w / img_asp_rat * canv_asp_rat};
    draw_img(hash, x, y, w, h);
  }

  void text_rend::init() {
    TTF_Init();
    add_fonts();
  }

  void text_rend::add_fonts() {
    auto abs_font_path{str(SDL_GetBasePath()) + k_default_font_path.data()};
    for (auto font_sz : {font_szs::_20, font_szs::_26}) {
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

  void text_rend::draw_str(str_view text, float x, float y, font_szs font_sz,
                           bool cent_align, color text_color) const {
    if (text.empty())
      return;
    auto font_raw{fonts_.at(font_sz).get()};
    auto sdl_color{text_color.to_sdl_color()};
    auto surf{TTF_RenderText_Blended(font_raw, text.data(), sdl_color)};

    // auto new_w{pow(2, std::ceil(log(surf->w) / log(2)))};
    // auto new_h{pow(2, std::ceil(log(surf->h) / log(2)))};

    auto new_w{surf->w};
    auto new_h{surf->h};

    sz text_dim;
    TTF_SizeText(font_raw, text.data(), &text_dim.w, &text_dim.h);
    SDL_Rect dest;
    auto canv_sz{get_canv_sz(_<sdl_device>().win())};
    dest.x = c_int(x * canv_sz.w);
    dest.y = c_int(y * canv_sz.h);
    dest.w = text_dim.w;
    dest.h = text_dim.h;
    if (cent_align) {
      dest.x -= dest.w / 2;
      dest.y -= dest.h / 2;
    }

    auto tex_already_exists{_<image_bank>().text_tex_exists(x, y)};
    auto tex{_<image_bank>().obtain_text_tex(x, y)};
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);                                // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function
    // if (!tex_already_exists) {
    glBindTexture(GL_TEXTURE_2D, tex);

    /* Load image file */

    /* Find out pixel format type */
    // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    if (!tex_already_exists) {
      auto intermediary = SDL_CreateRGBSurface(
          0, new_w, new_h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

      SDL_BlitSurface(surf, 0, intermediary, 0);

      glTexImage2D(GL_TEXTURE_2D, 0, 4, intermediary->w, intermediary->h, 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, intermediary->pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      SDL_FreeSurface(intermediary);
    }
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_TRIANGLE_FAN);

    auto xf{c_float(dest.x) / canv_sz.w};
    auto yf{c_float(dest.y) / canv_sz.h};
    auto wf{c_float(dest.w) / canv_sz.w};
    auto hf{c_float(dest.h) / canv_sz.h};

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xf, yf, 0.5f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xf + wf, yf, 0.5f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xf + wf, yf + hf, 0.5f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xf, yf + hf, 0.5f);

    glEnd();
    glFlush();

    // auto rend{_<sdl_device>().rend().get()};
    // auto tex{SDL_CreateTextureFromSurface(rend, surf)};
    // SDL_RenderCopy(rend, tex, nullptr, &dest);
    // SDL_DestroyTexture(tex);
    // SDL_FreeSurface(intermediary);
    SDL_FreeSurface(surf);
  }
}