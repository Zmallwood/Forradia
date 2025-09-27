/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateRenderer.hpp"

namespace Forradia
{
    SharedPtr<SDL_Renderer> CreateRenderer(SharedPtr<SDL_Window> window)
    {
        auto rendererResult{SharedPtr<SDL_Renderer>(
            SDL_CreateRenderer(
                window.get(),
                -1,
                SDL_RENDERER_ACCELERATED),
            SDLDeleter())};

        if (!rendererResult)
        {
            std::cout << "Renderer could not be created. SDL Error: "
                      << std::string(SDL_GetError()) << std::endl;
        }

        return rendererResult;
    }
}