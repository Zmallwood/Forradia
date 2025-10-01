/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "sdl_deleter.hpp"

namespace forr {
  void sdl_deleter::operator()(SDL_Window *window) const {
    // Free up resources from a SDL_Window object.
    SDL_DestroyWindow(window);
  }

  void sdl_deleter::operator()(SDL_Renderer *renderer) const {
    // Free up resources from a SDL_Renderer object.
    SDL_DestroyRenderer(renderer);
  }

  void sdl_deleter::operator()(SDL_Surface *surface) const {
    // Free up resources from a SDL_Surface object.
    SDL_FreeSurface(surface);
  }

  void sdl_deleter::operator()(SDL_Texture *texture) const {
    // Free up resources from a SDL_Texture object.
    SDL_DestroyTexture(texture);
  }

  void sdl_deleter::operator()(TTF_Font *font) const {
    // Free up resources from a TTF_Font object.
    TTF_CloseFont(font);
  }
}
