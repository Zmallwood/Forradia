/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_window.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  SharedPtr<SDL_Window> CreateWindow() {
    auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
               SDL_WINDOW_FULLSCREEN_DESKTOP};
    auto windowResult{SharedPtr<SDL_Window>(
        SDL_CreateWindow(
            GetSingleton<GameProperties>().k_gameWindowTitle.data(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 660, 660, flags),
        SDLDeleter())};
    if (!windowResult) {
      PrintLine("Window could not be created. SDL Error: " +
                String(SDL_GetError()));
    }
    return windowResult;
  }
}