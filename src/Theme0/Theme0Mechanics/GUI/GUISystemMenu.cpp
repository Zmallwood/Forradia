/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUISystemMenu.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"

namespace Forradia
{
    GUISystemMenu::GUISystemMenu()
        : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
    {
        SetVisible(false);
    }

    void GUISystemMenu::UpdateDerived()
    {
        GUIComponent::UpdateDerived();

        _<MouseInput>().GetLeftMouseButtonRef().Reset();
    }

    void GUISystemMenu::RenderDerived() const
    {
        GUIComponent::RenderDerived();

        auto canvasSize{GetCanvasSize()};

        auto rect{SDL_Rect{0, 0, canvasSize.width, canvasSize.height}};

        SDL_SetRenderDrawBlendMode(
            _<SDLDevice>().GetRenderer().get(),
            SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(
            _<SDLDevice>().GetRenderer().get(),
            200,
            0,
            255,
            50);

        SDL_RenderFillRect(
            _<SDLDevice>().GetRenderer().get(),
            &rect);
    }
}