//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "SDLDevice.hpp"

namespace Forradia {
    void SDLDevice::Initialize(StringView gameWindowTitle, Color clearColor) {
        m_gameWindowTitle = gameWindowTitle;
        m_clearColor = clearColor;
        SDL_Init(SDL_INIT_EVERYTHING);
        this->SetupSDLWindow();
    }

    void SDLDevice::ClearCanvas() const {
        auto clearColor{m_clearColor};
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SDLDevice::PresentCanvas() const {
        SDL_GL_SwapWindow(m_window.get());
    }

    Size SDLDevice::GetScreenSize() const {
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        auto width{displayMode.w};
        auto height{displayMode.h};
        return {width, height};
    }
}