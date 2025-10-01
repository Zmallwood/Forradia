/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  SDL_Rect CreateRenderDestinationRect(float x, float y, Size textDimensions,
                                       bool centerAlign);
}