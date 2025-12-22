/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"
#include "MessageUtilities.hpp"
#include "SDLDeleter.hpp"
#include "SDLDevice.hpp"

namespace Forradia
{
    auto SDLDevice::SetupSDLWindow() -> void
    {
        auto screenSize{SDLDevice::GetScreenSize()};

        m_window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(m_gameWindowTitle.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screenSize.width, screenSize.height,
                             k_windowFlags),
            SDLDeleter());

        if (m_window == nullptr)
        {
            ThrowError("Window could not be created. "
                       "SDL Error: " +
                       std::string(SDL_GetError()));
        }
    }
}
