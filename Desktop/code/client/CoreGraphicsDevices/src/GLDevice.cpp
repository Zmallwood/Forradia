/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GLDevice.hpp"
#include "ErrorUtilities.hpp"
#include "SDLDevice.hpp"
#include <SDL2/SDL.h>
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia
{
    GLDevice::~GLDevice()
    {
        SDL_GL_DeleteContext(*m_context);
    }

    auto GLDevice::Initialize() -> void
    {
        this->SetupGL();
    }

    auto GLDevice::SetupGL() -> void
    {
        auto window{SDLDevice::Instance().GetWindow()};

        m_context = std::make_shared<SDL_GLContext>(SDL_GL_CreateContext(window.get()));

        SDL_GL_MakeCurrent(window.get(), *m_context);

        GLenum status{glewInit()};

        if (GLEW_OK != status)
        {
            auto errorString{
                std::string(reinterpret_cast<const char *>(glewGetErrorString(status)))};

            ThrowError("GLEW error: " + errorString);
        }

        // Turn of vertical sync.
        SDL_GL_SetSwapInterval(0);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
    }
}
