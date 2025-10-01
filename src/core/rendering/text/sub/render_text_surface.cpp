/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "render_text_surface.hpp"
#include "create_render_destination_rect.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  void RenderTextSurface(SDL_Surface *surface, float x, float y,
                         Size textDimensions, bool centerAlign) {
    auto destinationRect{
        CreateRenderDestinationRect(x, y, textDimensions, centerAlign)};
    auto renderer{GetSingleton<SDLDevice>().GetRenderer().get()};
    auto texture{SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_RenderCopy(renderer, texture, nullptr, &destinationRect);
    SDL_DestroyTexture(texture);
  }
}