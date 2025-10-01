/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_rendered_text_surface.hpp"

namespace forr {
  SDL_Surface *get_rendered_text_surface(str_view text, TTF_Font *fontRaw,
                                         color textColor) {
    auto sdlColor{textColor.to_sdl_color()};
    auto surfaceResult{TTF_RenderText_Solid(fontRaw, text.data(), sdlColor)};
    return surfaceResult;
  }
}