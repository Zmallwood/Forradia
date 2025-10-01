/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_system_menu.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  void gui_system_menu::Initialize() { SetVisible(false); }

  void gui_system_menu::UpdateDerived() {
    gui_component::UpdateDerived();
    GetSingleton<mouse_input>().GetLeftMouseButtonRef().Reset();
  }

  void gui_system_menu::RenderDerived() const {
    gui_component::RenderDerived();
    auto canvasSize{GetCanvasSize()};
    auto rect{SDL_Rect{0, 0, canvasSize.width, canvasSize.height}};
    SDL_SetRenderDrawBlendMode(GetSingleton<sdl_device>().GetRenderer().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(GetSingleton<sdl_device>().GetRenderer().get(), 200,
                           0, 255, 50);
    SDL_RenderFillRect(GetSingleton<sdl_device>().GetRenderer().get(), &rect);
  }
}