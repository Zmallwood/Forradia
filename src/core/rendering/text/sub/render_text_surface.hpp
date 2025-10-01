/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  void render_text_surface(SDL_Surface *surface, float x, float y,
                           size textDimensions, bool centerAlign);
}