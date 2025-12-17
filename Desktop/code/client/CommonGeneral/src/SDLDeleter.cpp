/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "SDLDeleter.hpp"

namespace Forradia {
auto SDLDeleter::operator()(SDL_Window *window) const -> void {
  SDL_DestroyWindow(window);
}

auto SDLDeleter::operator()(SDL_Renderer *renderer) const -> void {
  SDL_DestroyRenderer(renderer);
}

auto SDLDeleter::operator()(SDL_Surface *surface) const -> void {
  SDL_FreeSurface(surface);
}

auto SDLDeleter::operator()(SDL_Texture *texture) const -> void {
  SDL_DestroyTexture(texture);
}

auto SDLDeleter::operator()(TTF_Font *font) const -> void {
  TTF_CloseFont(font);
}
}