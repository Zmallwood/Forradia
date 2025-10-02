/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  SDL_Surface *get_rendered_text_surface(str_view text, TTF_Font *font_raw,
                                         color text_color);
}