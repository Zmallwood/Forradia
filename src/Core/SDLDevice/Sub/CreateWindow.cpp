/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateWindow.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"

namespace Forradia
{
    SharedPtr<SDL_Window> CreateWindow()
    {
        auto flags{
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_RESIZABLE |
            SDL_WINDOW_MAXIMIZED |
            SDL_WINDOW_FULLSCREEN_DESKTOP};

        auto windowResult{SharedPtr<SDL_Window>(
            SDL_CreateWindow(_<GameProperties>().k_gameWindowTitle.data(),
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             660,
                             660,
                             flags),
            SDLDeleter())};

        if (!windowResult)
        {
            std::cout << "Window could not be created. SDL Error: "
                      << String(SDL_GetError()) << std::endl;
        }

        return windowResult;
    }
}