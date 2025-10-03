/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "render_text_surface.hpp"
#include "core/core.hpp"
#include "create_render_destination_rect.hpp"

namespace forr {
  void render_text_surface(SDL_Surface *surf, float x, float y, size text_dim,
                           bool cent_align) {
    auto dest_rect{create_render_destination_rect(x, y, text_dim, cent_align)};
    auto rend{get_ston<sdl_device>().get_rend().get()};
    auto tex{SDL_CreateTextureFromSurface(rend, surf)};
    SDL_RenderCopy(rend, tex, nullptr, &dest_rect);
    SDL_DestroyTexture(tex);
  }
}