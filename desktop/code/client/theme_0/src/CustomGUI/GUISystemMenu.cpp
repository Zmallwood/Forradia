//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUISystemMenu.hpp"

#include "Input/Mouse/MouseInput.hpp"

namespace Forradia::Theme0
{
    void GUISystemMenu::Initialize()
    {
        this->SetVisible(false);
    }

    void GUISystemMenu::UpdateDerived()
    {
        GUIComponent::UpdateDerived();

        _<MouseInput>().GetLeftMouseButtonRef().Reset();
    }

    void GUISystemMenu::RenderDerived() const
    {
        GUIComponent::RenderDerived();

        // auto
        // c_sz{GetCanvasSize(_<SDLDevice>().GetWindow())};

        // auto rect{SDL_Rect{0, 0, c_sz.w,
        // c_sz.h}};

        // SDL_SetRenderDrawBlendMode(_<SDLDevice>().rend().get(),
        //                            SDL_BLENDMODE_BLEND);

        // SDL_SetRenderDrawColor(_<SDLDevice>().rend().get(),
        // 200, 0,
        //                        255, 50);

        // SDL_RenderFillRect(_<SDLDevice>().rend().get(),
        // &rect);
    }
}