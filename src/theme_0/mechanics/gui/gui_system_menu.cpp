/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_system_menu.hpp"
#include "core/core.hpp"
#include "core/input.hpp"

namespace forr {
  void gui_system_menu::initialize() { set_visible(false); }

  void gui_system_menu::update_derived() {
    gui_component::update_derived();
    get_singleton<mouse_input>().get_left_mouse_button_ref().reset();
  }

  void gui_system_menu::render_derived() const {
    gui_component::render_derived();
    auto canvas_size{get_canvas_size()};
    auto rect{SDL_Rect{0, 0, canvas_size.w, canvas_size.h}};
    SDL_SetRenderDrawBlendMode(get_singleton<sdl_device>().get_renderer().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(get_singleton<sdl_device>().get_renderer().get(),
                           200, 0, 255, 50);
    SDL_RenderFillRect(get_singleton<sdl_device>().get_renderer().get(), &rect);
  }
}