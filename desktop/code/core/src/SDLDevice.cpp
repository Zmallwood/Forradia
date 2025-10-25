//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SDLDevice.hpp"

namespace Forradia
{
    SDLDevice::~SDLDevice()
    {
        SDL_GL_DeleteContext(*m_context);
    }

    void SDLDevice::Initialize(StringView gameWindowTitle,
                               Color clearColor)
    {
        m_gameWindowTitle = gameWindowTitle;
        m_clearColor = clearColor;

        SDL_Init(SDL_INIT_EVERYTHING);

        SetupSDLWindow();

        SetupGL();
    }

    void SDLDevice::SetupGL()
    {
        m_context = std::make_shared<SDL_GLContext>(
            SDL_GL_CreateContext(m_window.get()));

        SDL_GL_MakeCurrent(m_window.get(), *m_context);

        GLenum status{glewInit()};

        if (GLEW_OK != status)
        {
            printf("GLEW Error: ",
                   glewGetErrorString(status));
        }

        SDL_GL_SetSwapInterval(0);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
    }

    void SDLDevice::ClearCanvas() const
    {
        auto clearColor{m_clearColor.ToSDLColor()};

        glClearColor(clearColor.r, clearColor.g,
                     clearColor.b, clearColor.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SDLDevice::PresentCanvas() const
    {
        SDL_GL_SwapWindow(m_window.get());
    }

    Size SDLDevice::GetScreenSize() const
    {
        SDL_DisplayMode displayMode;

        SDL_GetCurrentDisplayMode(0, &displayMode);

        auto width{displayMode.w};
        auto height{displayMode.h};

        return {width, height};
    }
}