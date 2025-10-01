/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_renderer.hpp"

namespace forr {
  s_ptr<SDL_Renderer> CreateRenderer(s_ptr<SDL_Window> window) {
    auto rendererResult{s_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
        sdl_deleter())};
    if (!rendererResult) {
      PrintLine("Renderer could not be created. SDL Error: " +
                std::string(SDL_GetError()));
    }
    return rendererResult;
  }
}