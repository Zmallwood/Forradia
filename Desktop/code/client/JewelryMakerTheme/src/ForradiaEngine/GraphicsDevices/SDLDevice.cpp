/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "SDLDevice.hpp"
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/Common/General.hpp"
    #include <GL/gl.h>
// clang-format on

namespace ForradiaEngine
{
    auto SDLDevice::initialize(std::string_view gameWindowTitle, Color clearColor) -> void
    {
        m_gameWindowTitle = gameWindowTitle;
        m_clearColor = clearColor;

        SDL_Init(SDL_INIT_EVERYTHING);

        this->setupSDLWindow();
    }

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

    auto SDLDevice::clearCanvas() const -> void
    {
        auto clearColor{m_clearColor};
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    auto SDLDevice::presentCanvas() const -> void
    {
        SDL_GL_SwapWindow(m_window.get());
    }

    auto SDLDevice::getScreenSize() -> Size
    {
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);

        auto width{displayMode.w};
        auto height{displayMode.h};

        return {width, height};
    }
}
