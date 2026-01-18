/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GLDevice.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "ForradiaEngine/Common/Utilities.hpp"
#include "SDLDevice.hpp"

namespace ForradiaEngine
{
    GLDevice::~GLDevice()
    {
        SDL_GL_DeleteContext(*m_context);
    }

    auto GLDevice::initialize() -> void
    {
        this->setupGL();
    }

    auto GLDevice::setupGL() -> void
    {
        auto window{SDLDevice::instance().getWindow()};

        m_context = std::make_shared<SDL_GLContext>(SDL_GL_CreateContext(window.get()));

        SDL_GL_MakeCurrent(window.get(), *m_context);

        GLenum status{glewInit()};

        If(GLEW_OK != status)
        {
            auto errorString{
                std::string(reinterpret_cast<const char *>(glewGetErrorString(status)))};

            throwError("GLEW error: " + errorString);
        }

        // Turn of vertical sync.
        SDL_GL_SetSwapInterval(0);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
    }
}
