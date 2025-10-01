/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  SDL_Surface *GetRenderedTextSurface(StringView text, TTF_Font *fontRaw,
                                      Color textColor);
}