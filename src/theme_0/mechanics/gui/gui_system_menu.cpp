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
    get_ston<mouse_input>().get_left_btn_ref().reset();
  }

  void gui_system_menu::render_derived() const {
    gui_component::render_derived();
    auto canv_sz{get_canv_sz()};
    auto rect{SDL_Rect{0, 0, canv_sz.w, canv_sz.h}};
    SDL_SetRenderDrawBlendMode(get_ston<sdl_device>().get_rend().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(get_ston<sdl_device>().get_rend().get(), 200, 0,
                           255, 50);
    SDL_RenderFillRect(get_ston<sdl_device>().get_rend().get(), &rect);
  }
}