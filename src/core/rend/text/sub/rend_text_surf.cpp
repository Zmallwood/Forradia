/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "rend_text_surf.hpp"
#include "core/core.hpp"
#include "create_rend_dest_rect.hpp"

namespace forr {
  void rend_text_surf(SDL_Surface *surf, float x, float y, size text_dim,
                      bool cent_align) {
    auto dest_rect{create_rend_dest_rect(x, y, text_dim, cent_align)};
    auto rend{get_ston<sdl_device>().get_rend().get()};
    auto tex{SDL_CreateTextureFromSurface(rend, surf)};
    SDL_RenderCopy(rend, tex, nullptr, &dest_rect);
    SDL_DestroyTexture(tex);
  }
}