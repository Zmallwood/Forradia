//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SDLDevice.hpp"

namespace Forradia
{
    SDLDevice::SDLDevice()
    {
        m_window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow("Forradia Map Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED),
            SDLDeleter());
        m_renderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED), SDLDeleter());
    }

    void SDLDevice::ClearCanvas()
    {
        SDL_SetRenderDrawColor(m_renderer.get(), 0, 150, 255, 255);
        SDL_RenderClear(m_renderer.get());
    }

    void SDLDevice::PresentCanvas()
    {
        SDL_RenderPresent(m_renderer.get());
    }
}