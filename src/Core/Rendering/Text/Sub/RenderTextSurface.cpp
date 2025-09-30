/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "RenderTextSurface.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "CreateRenderDestinationRect.hpp"

namespace Forradia {
  void RenderTextSurface(SDL_Surface *surface, float x, float y,
                         Size textDimensions, bool centerAlign) {
    auto destinationRect{
        CreateRenderDestinationRect(x, y, textDimensions, centerAlign)};

    auto renderer{_<SDLDevice>().GetRenderer().get()};

    auto texture{SDL_CreateTextureFromSurface(renderer, surface)};

    SDL_RenderCopy(renderer, texture, nullptr, &destinationRect);

    SDL_DestroyTexture(texture);
  }
}