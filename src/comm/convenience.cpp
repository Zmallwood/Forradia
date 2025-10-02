/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "convenience.hpp"

namespace forr {
  void sdl_deleter::operator()(SDL_Window *win) const {
    // Free up resources from a SDL_Window object.
    SDL_DestroyWindow(win);
  }

  void sdl_deleter::operator()(SDL_Renderer *rend) const {
    // Free up resources from a SDL_Renderer object.
    SDL_DestroyRenderer(rend);
  }

  void sdl_deleter::operator()(SDL_Surface *surf) const {
    // Free up resources from a SDL_Surface object.
    SDL_FreeSurface(surf);
  }

  void sdl_deleter::operator()(SDL_Texture *tex) const {
    // Free up resources from a SDL_Texture object.
    SDL_DestroyTexture(tex);
  }

  void sdl_deleter::operator()(TTF_Font *font) const {
    // Free up resources from a TTF_Font object.
    TTF_CloseFont(font);
  }
}