//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SDLDevice.hpp"

namespace Forradia
{
    void SDLDevice::Initialize(StringView gameWindowTitle,
                               Color clearColor)
    {
        // Set the game window title and clear color.

        m_gameWindowTitle = gameWindowTitle;

        m_clearColor = clearColor;

        // Do necessary SDL initialization.

        SDL_Init(SDL_INIT_EVERYTHING);

        // Setup the SDL window.

        this->SetupSDLWindow();
    }

    void SDLDevice::ClearCanvas() const
    {
        // Get converted clear color.

        auto clearColor{m_clearColor.ToSDLColor()};

        // Set the clear color.

        glClearColor(clearColor.r, clearColor.g,
                     clearColor.b, clearColor.a);

        // Clear the canvas.

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SDLDevice::PresentCanvas() const
    {
        // Swap the window to show the rendered frame.

        SDL_GL_SwapWindow(m_window.get());
    }

    Size SDLDevice::GetScreenSize() const
    {
        // To hold the display mode.

        SDL_DisplayMode displayMode;

        // Get the display mode.

        SDL_GetCurrentDisplayMode(0, &displayMode);

        // Pick the width and height.

        auto width{displayMode.w};

        auto height{displayMode.h};

        // Return the size.

        return {width, height};
    }
}