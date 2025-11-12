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
        // Cleanup the context.

        SDL_GL_DeleteContext(*m_context);
    }

    void GLDevice::Initialize()
    {
        // Setup the opengl functionality.

        this->SetupGL();
    }

    void GLDevice::SetupGL()
    {
        // Get the SDL window.

        auto window{_<SDLDevice>().GetWindow()};

        // Create the opengl context.

        m_context = std::make_shared<SDL_GLContext>(
            SDL_GL_CreateContext(window.get()));

        // Make the context current.

        SDL_GL_MakeCurrent(window.get(), *m_context);

        // Initialize GLEW.

        GLenum status{glewInit()};

        // Check that GLEW was initialized successfully.

        if (GLEW_OK != status)
        {
            // Get the error string.

            auto errorString{
                String(reinterpret_cast<const char *>(
                    glewGetErrorString(status)))};

            // Print the error string.

            PrintLine("GLEW error: " + errorString);
        }

        // Turn of vertical sync.

        SDL_GL_SetSwapInterval(0);

        // Enable textures.

        glEnable(GL_TEXTURE_2D);

        // Enable blending.

        glEnable(GL_BLEND);
    }
}