/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_system_menu.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  void gui_system_menu::initialize() { set_visible(false); }

  void gui_system_menu::update_derived() {
    gui_component::update_derived();
    GetSingleton<mouse_input>().get_left_mouse_button_ref().reset();
  }

  void gui_system_menu::render_derived() const {
    gui_component::render_derived();
    auto canvasSize{GetCanvasSize()};
    auto rect{SDL_Rect{0, 0, canvasSize.width, canvasSize.height}};
    SDL_SetRenderDrawBlendMode(GetSingleton<sdl_device>().get_renderer().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(GetSingleton<sdl_device>().get_renderer().get(), 200,
                           0, 255, 50);
    SDL_RenderFillRect(GetSingleton<sdl_device>().get_renderer().get(), &rect);
  }
}