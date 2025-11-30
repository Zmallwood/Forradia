//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SDLDevice.hpp"

namespace AAK
{
    namespace Forradia
    {
        void SDLDevice::SetupSDLWindow()
        {
            // Get the screen size.

            auto screenSize{this->GetScreenSize()};

            // Create the SDL window.

            m_window = SharedPtr<SDL_Window>(
                SDL_CreateWindow(m_gameWindowTitle.data(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, screenSize.width, screenSize.height,
                                 k_windowFlags),
                SDLDeleter());

            // Check that the window was created successfully.

            if (nullptr == m_window)
            {
                PrintLine("Window could not be created. "
                          "SDL Error: " +
                          String(SDL_GetError()));
            }
        }
    }
}