/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
    #include "ForradiaEngine/Common/General/SDLDeleter.hpp"
    #include "SDLDevice.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto SDLDevice::setupSDLWindow() -> void
    {
        auto screenSize{SDLDevice::getScreenSize()};

        m_window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(m_gameWindowTitle.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screenSize.width, screenSize.height,
                             k_windowFlags),
            SDLDeleter());

        if (m_window == nullptr)
        {
            throwError("Window could not be created. "
                       "SDL Error: " +
                       std::string(SDL_GetError()));
        }
    }
}
