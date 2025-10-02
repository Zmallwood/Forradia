/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "render_text_surface.hpp"
#include "core/sdl_device/sdl_device.hpp"
#include "create_render_destination_rect.hpp"

namespace forr {
  void render_text_surface(SDL_Surface *surface, float x, float y,
                           size text_dimensions, bool center_align) {
    auto dest_rect{
        create_render_destination_rect(x, y, text_dimensions, center_align)};
    auto renderer{get_singleton<sdl_device>().get_renderer().get()};
    auto texture{SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
    SDL_DestroyTexture(texture);
  }
}