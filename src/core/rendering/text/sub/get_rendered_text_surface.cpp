/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_rendered_text_surface.hpp"

namespace forr {
  SDL_Surface *GetRenderedTextSurface(StringView text, TTF_Font *fontRaw,
                                      Color textColor) {
    auto sdlColor{textColor.ToSDLColor()};
    auto surfaceResult{TTF_RenderText_Solid(fontRaw, text.data(), sdlColor)};
    return surfaceResult;
  }
}