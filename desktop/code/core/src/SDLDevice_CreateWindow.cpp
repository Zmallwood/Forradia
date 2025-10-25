//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SDLDevice.hpp"

namespace Forradia
{
    void SDLDevice::SetupSDLWindow()
    {
        auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                   SDL_WINDOW_MAXIMIZED |
                   SDL_WINDOW_FULLSCREEN_DESKTOP |
                   SDL_WINDOW_OPENGL};

        auto screenSize{GetScreenSize()};

        auto windowResult{SharedPtr<SDL_Window>(
            SDL_CreateWindow(m_gameWindowTitle.data(),
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             screenSize.width,
                             screenSize.height, flags),
            SDLDeleter())};

        if (!windowResult)
        {
            PrintLine("Window could not be created. "
                      "SDL Error: " +
                      String(SDL_GetError()));
        }

        m_window = windowResult;
    }
}