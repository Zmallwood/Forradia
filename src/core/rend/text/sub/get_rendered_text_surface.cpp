/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_rendered_text_surface.hpp"

namespace forr {
  SDL_Surface *get_rendered_text_surface(str_view text, TTF_Font *font_raw,
                                         color text_color) {
    auto sdl_color{text_color.to_sdl_color()};
    auto surf_res{TTF_RenderText_Solid(font_raw, text.data(), sdl_color)};
    return surf_res;
  }
}