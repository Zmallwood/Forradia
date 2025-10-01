/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_system_menu.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  void GUISystemMenu::Initialize() { SetVisible(false); }

  void GUISystemMenu::UpdateDerived() {
    GUIComponent::UpdateDerived();
    GetSingleton<MouseInput>().GetLeftMouseButtonRef().Reset();
  }

  void GUISystemMenu::RenderDerived() const {
    GUIComponent::RenderDerived();
    auto canvasSize{GetCanvasSize()};
    auto rect{SDL_Rect{0, 0, canvasSize.width, canvasSize.height}};
    SDL_SetRenderDrawBlendMode(GetSingleton<SDLDevice>().GetRenderer().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(GetSingleton<SDLDevice>().GetRenderer().get(), 200,
                           0, 255, 50);
    SDL_RenderFillRect(GetSingleton<SDLDevice>().GetRenderer().get(), &rect);
  }
}