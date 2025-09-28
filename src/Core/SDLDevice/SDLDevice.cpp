/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "SDLDevice.hpp"
#include "Sub/CreateWindow.hpp"
#include "Sub/CreateRenderer.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"

namespace Forradia
{
    void SDLDevice::Initialize()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        m_window = CreateWindow();

        if (m_window)
        {
            m_renderer = CreateRenderer(m_window);
        }
    }

    void SDLDevice::ClearCanvas() const
    {
        SDL_Color clearColor{
            _<GameProperties>().k_clearColor.ToSDLColor()};

        SDL_SetRenderDrawColor(
            m_renderer.get(),
            clearColor.r,
            clearColor.g,
            clearColor.b,
            255);

        SDL_RenderClear(m_renderer.get());
    }

    void SDLDevice::PresentCanvas() const
    {
        SDL_RenderPresent(m_renderer.get());
    }
}
