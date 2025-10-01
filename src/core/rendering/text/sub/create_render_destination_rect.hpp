/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  SDL_Rect create_render_destination_rect(float x, float y, size textDimensions,
                                          bool centerAlign);
}