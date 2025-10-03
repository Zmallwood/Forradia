/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  SDL_Rect create_rend_dest_rect(float x, float y, size text_dim,
                                 bool cent_align);
}