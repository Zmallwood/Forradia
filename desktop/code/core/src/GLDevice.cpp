//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GLDevice.hpp"
#include "SDLDevice.hpp"

namespace Forradia
{
    GLDevice::~GLDevice()
    {
        SDL_GL_DeleteContext(*m_context);
    }

    void GLDevice::Initialize()
    {
        SetupGL();
    }

    void GLDevice::SetupGL()
    {
        auto window{_<SDLDevice>().GetWindow()};

        m_context = std::make_shared<SDL_GLContext>(
            SDL_GL_CreateContext(window.get()));

        SDL_GL_MakeCurrent(window.get(), *m_context);

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
}